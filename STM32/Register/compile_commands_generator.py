#!/usr/bin/env python
"""
通用编译命令生成器
根据compile_flags.txt为项目生成compile_commands.json
支持自动发现源文件和自定义配置

基本用法:python compile_commands_generator.py

# 完整参数示例
python compile_commands_generator.py \
    --project /path/to/project \
    --flags my_compile_flags.txt \
    --output build/compile_commands.json \
    --dirs User Driver ExternalLib \
    --create-clangd

"""

import os
import sys
import json
import glob
import argparse

class CompileCommandsGenerator:
    def __init__(self, project_root="."):
        self.project_root = os.path.abspath(project_root)
        self.source_extensions = {
            '.c', '.C', '.cpp', '.cc', '.cxx', 
            '.h', '.H', '.hpp', '.hh', '.hxx',
            '.s', '.S'  # 汇编文件
        }
        self.exclude_dirs = {
            'build', 'cmake-build-debug', 'cmake-build-release',
            '.git', '.vscode', '.vs', '.idea', 'obj', 'bin'
        }
    
    def load_compile_flags(self, flags_file="compile_flags.txt"):
        """加载编译标志文件"""
        flags_path = os.path.join(self.project_root, flags_file)
        if not os.path.exists(flags_path):
            print(f"错误: 找不到编译标志文件 {flags_path}")
            return None
        
        with open(flags_path, 'r', encoding='utf-8') as f:
            flags = [line.strip() for line in f if line.strip() and not line.startswith('#')]
        
        # 自动提取编译器（如果有指定）
        compiler = "gcc"
        for flag in flags[:]:  # 使用副本遍历，以便修改原列表
            if flag.startswith('-compiler='):
                compiler = flag.split('=', 1)[1]
                flags.remove(flag)  # 从标志中移除编译器指定
                break
        
        return {
            'compiler': compiler,
            'flags': flags
        }
    
    def find_source_files(self, additional_dirs=None):
        """查找项目中的所有源文件"""
        source_files = []
        
        # 默认搜索目录
        search_dirs = [self.project_root]
        
        # 添加额外的搜索目录
        if additional_dirs:
            for dir_path in additional_dirs:
                full_path = os.path.join(self.project_root, dir_path)
                if os.path.exists(full_path):
                    search_dirs.append(full_path)
        
        # 查找文件
        for search_dir in search_dirs:
            for root, dirs, files in os.walk(search_dir):
                # 排除不需要的目录
                dirs[:] = [d for d in dirs if d not in self.exclude_dirs and not d.startswith('.')]
                
                for file in files:
                    ext = os.path.splitext(file)[1]
                    if ext in self.source_extensions:
                        full_path = os.path.join(root, file)
                        source_files.append(full_path)
        
        return source_files
    
    def generate_output_path(self, source_file):
        """为源文件生成输出路径"""
        # 获取相对于项目根目录的路径
        rel_path = os.path.relpath(source_file, self.project_root)
        # 将路径分隔符统一为 /
        rel_path = rel_path.replace('\\', '/')
        
        # 生成输出文件名
        base_name = os.path.splitext(rel_path)[0]
        output_file = f"obj/{base_name}.o"
        
        return output_file
    
    def generate_compile_commands(self, flags_config, source_files):
        """生成编译命令条目"""
        entries = []
        
        for source_file in source_files:
            output_file = self.generate_output_path(source_file)
            
            # 确保输出目录存在
            output_dir = os.path.dirname(output_file)
            os.makedirs(output_dir, exist_ok=True)
            
            # 构建编译命令参数
            arguments = [flags_config['compiler']]
            arguments.extend(flags_config['flags'])
            arguments.extend(['-c', source_file, '-o', output_file])
            
            entry = {
                "directory": self.project_root,
                "file": source_file,
                "arguments": arguments,
                "output": output_file
            }
            
            entries.append(entry)
        
        return entries
    
    def save_compile_commands(self, entries, output_file="compile_commands.json"):
        """保存编译命令到JSON文件"""
        output_path = os.path.join(self.project_root, output_file)
        
        with open(output_path, 'w', encoding='utf-8') as f:
            json.dump(entries, f, indent=2, ensure_ascii=False)
        
        return output_path
    
    def create_clangd_config(self):
        """创建.clangd配置文件"""
        clangd_config = """CompileFlags:
  Add: []
  
Index:
  Background: Skip
  
Diagnostics:
  ClangTidy:
    Remove: [readability-magic-numbers]
"""
        
        config_path = os.path.join(self.project_root, '.clangd')
        with open(config_path, 'w', encoding='utf-8') as f:
            f.write(clangd_config)
        
        return config_path

def main():
    parser = argparse.ArgumentParser(description="通用编译命令生成器")
    parser.add_argument("--project", "-p", default=".", 
                       help="项目根目录 (默认: 当前目录)")
    parser.add_argument("--flags", "-f", default="compile_flags.txt",
                       help="编译标志文件 (默认: compile_flags.txt)")
    parser.add_argument("--output", "-o", default="compile_commands.json",
                       help="输出文件 (默认: compile_commands.json)")
    parser.add_argument("--dirs", "-d", nargs="*",
                       help="额外的源文件目录")
    parser.add_argument("--create-clangd", action="store_true",
                       help="创建.clangd配置文件")
    
    args = parser.parse_args()
    
    # 创建生成器实例
    generator = CompileCommandsGenerator(args.project)
    
    # 加载编译标志
    flags_config = generator.load_compile_flags(args.flags)
    if not flags_config:
        return 1
    
    print(f"使用编译器: {flags_config['compiler']}")
    print(f"编译标志数量: {len(flags_config['flags'])}")
    
    # 查找源文件
    source_files = generator.find_source_files(args.dirs)
    print(f"找到源文件: {len(source_files)} 个")
    
    # 生成编译命令
    entries = generator.generate_compile_commands(flags_config, source_files)
    
    # 保存编译命令
    output_path = generator.save_compile_commands(entries, args.output)
    print(f"编译命令已保存到: {output_path}")
    
    # 创建.clangd配置文件（如果指定）
    if args.create_clangd:
        config_path = generator.create_clangd_config()
        print(f"Clangd配置已保存到: {config_path}")
    
    # 显示统计信息
    print("\n项目统计:")
    file_types = {}
    for file in source_files:
        ext = os.path.splitext(file)[1]
        file_types[ext] = file_types.get(ext, 0) + 1
    
    for ext, count in sorted(file_types.items()):
        print(f"  {ext}: {count} 个文件")
    
    return 0

if __name__ == '__main__':
    sys.exit(main())
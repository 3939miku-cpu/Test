#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
生成海报 SVG 矢量图 - 严格按照昨天版本，只添加指导老师
"""

svg_content = '''<?xml version="1.0" encoding="UTF-8"?>
<svg xmlns="http://www.w3.org/2000/svg" viewBox="0 0 595 842">
  <defs>
    <linearGradient id="headerGrad" x1="0%" y1="0%" x2="0%" y2="100%">
      <stop offset="0%" style="stop-color:#003366"/>
      <stop offset="100%" style="stop-color:#001E3C"/>
    </linearGradient>
    <linearGradient id="footerGrad" x1="0%" y1="0%" x2="0%" y2="100%">
      <stop offset="0%" style="stop-color:#001E3C"/>
      <stop offset="100%" style="stop-color:#003366"/>
    </linearGradient>
  </defs>
  
  <!-- 背景 -->
  <rect width="595" height="842" fill="white"/>
  
  <!-- 右上角装饰菱形 -->
  <g transform="translate(420, 180) rotate(45)">
    <rect x="0" y="0" width="100" height="100" fill="none" stroke="#4F81BD" stroke-width="2" opacity="0.3"/>
    <rect x="15" y="15" width="70" height="70" fill="none" stroke="#4F81BD" stroke-width="1" opacity="0.5"/>
  </g>
  
  <!-- 头部区域（深蓝色背景） -->
  <rect width="595" height="120" fill="url(#headerGrad)"/>
  <text x="297.5" y="50" text-anchor="middle" fill="white" font-family="SimSun, serif" font-size="28" font-weight="bold" letter-spacing="3">凤起南航·泰达未来</text>
  <text x="297.5" y="85" text-anchor="middle" fill="#4F81BD" font-family="SimSun, serif" font-size="14" letter-spacing="2">民航创新实践挑战赛</text>
  
  <!-- 赛道信息（浅蓝色背景） -->
  <rect y="120" width="595" height="35" fill="#4F81BD"/>
  <text x="297.5" y="144" text-anchor="middle" fill="white" font-family="SimSun, serif" font-size="13" font-weight="bold" letter-spacing="2">飞行器适航技术方向 · 参赛作品</text>
  
  <!-- 作品标题 -->
  <text x="297.5" y="210" text-anchor="middle" fill="#001E3C" font-family="SimSun, serif" font-size="20" font-weight="bold">面向城市物流无人机的</text>
  <text x="297.5" y="245" text-anchor="middle" fill="#001E3C" font-family="SimSun, serif" font-size="20" font-weight="bold">适航合规性检查清单设计</text>
  
  <!-- 分隔线 -->
  <line x1="247.5" y1="265" x2="347.5" y2="265" stroke="#4F81BD" stroke-width="3"/>
  
  <!-- 作品简介 -->
  <text x="297.5" y="295" text-anchor="middle" fill="#666666" font-family="SimSun, serif" font-size="11">基于国令第 761 号、CCAR-21-R4、CCAR-92 等最新法规框架</text>
  <text x="297.5" y="315" text-anchor="middle" fill="#666666" font-family="SimSun, serif" font-size="11">6 大类 32 项检查内容 · A/B/C 三级适航评级</text>
  <text x="297.5" y="335" text-anchor="middle" fill="#666666" font-family="SimSun, serif" font-size="11">20 分钟内完成检查 · 事故率降低约 30%</text>
  
  <!-- 核心创新点标题 -->
  <rect x="80" y="370" width="4" height="20" fill="#003366"/>
  <text x="95" y="386" fill="#003366" font-family="SimSun, serif" font-size="16" font-weight="bold">核心创新点</text>
  
  <!-- 创新点 1（浅色框） -->
  <rect x="80" y="410" width="435" height="45" fill="#F5F7FA" rx="5"/>
  <text x="95" y="438" fill="#333333" font-family="SimSun, serif" font-size="12">✓ 操作简便 — 20 分钟内完成全部检查，一线操作员可快速上手</text>
  
  <!-- 创新点 2（浅色框） -->
  <rect x="80" y="465" width="435" height="45" fill="#F5F7FA" rx="5"/>
  <text x="95" y="493" fill="#333333" font-family="SimSun, serif" font-size="12">✓ 场景适配 — 针对城市物流定制检查项（货物固定、隐私保护、噪音控制）</text>
  
  <!-- 创新点 3（浅色框） -->
  <rect x="80" y="520" width="435" height="45" fill="#F5F7FA" rx="5"/>
  <text x="95" y="548" fill="#333333" font-family="SimSun, serif" font-size="12">✓ 分级管理 — A/B/C 三级适航评级，实现差异化风险管理</text>
  
  <!-- 底部区域（深蓝色背景） -->
  <rect y="680" width="595" height="162" fill="url(#footerGrad)"/>
  <text x="297.5" y="730" text-anchor="middle" fill="white" font-family="SimSun, serif" font-size="14">指导老师：李维</text>
  <text x="297.5" y="765" text-anchor="middle" fill="white" font-family="SimSun, serif" font-size="14">参赛队员：032580219 王徐嘉</text>
  <text x="297.5" y="805" text-anchor="middle" fill="#4F81BD" font-family="SimSun, serif" font-size="16" font-weight="bold">南京航空航天大学</text>
</svg>
'''

# 保存 SVG 文件
output_path = '/home/admin/.openclaw/workspace/nuca-competition/参赛作品海报.svg'
with open(output_path, 'w', encoding='utf-8') as f:
    f.write(svg_content)

print(f'海报 SVG 已生成：{output_path}')

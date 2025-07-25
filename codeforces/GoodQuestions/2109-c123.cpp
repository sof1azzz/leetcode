//
// Created by 123 on 25-7-25.
//
/*
* x ❖ 问题描述
欢迎，决斗者！在这个交互式挑战中，有一个未知的整数 x，满足：
  1 ≤ x ≤ 10^9。

你的任务是通过一系列操作将 x 变成给定的目标整数 n。

你可以发送如下四种指令之一，每条指令都会收到评测器（Jury）返回的反馈：

❖ 可用指令
命令	限制条件	结果（res）	状态更新	评测器返回
add y	−10<sup>18</sup> ≤ y ≤ 10<sup>18</sup>	res = x + y	如果 1 ≤ res ≤ 10<sup>18</sup>，则 x ← res，否则 x 不变	"1" 或 "0"
mul y	1 ≤ y ≤ 10<sup>18</sup>	res = x × y	如果 1 ≤ res ≤ 10<sup>18</sup>，则 x ← res，否则 x 不变	"1" 或 "0"
div y	1 ≤ y ≤ 10<sup>18</sup>	res = x ÷ y	如果 y 能整除 x，则 x ← res，否则 x 不变	"1" 或 "0"
digit	—	res = S(x)
（x 各位数字之和）	x ← res	总是返回 "1"

❖ 数字和函数说明
函数 S(x) 表示 x 的各位数字之和。

例如：
  S(123) = 1 + 2 + 3 = 6
*/

// 1。 限制7次指令。 可以发现实行两次digit指令可以把数字压缩到[1,16]
// 因为最大是1e9，数位和是81，再来一次最大的数位和是79，就是16
// 然后-8,-4,-2,-1,最后变成了1，然后加n-1

// 2。 限制4次指令。 比较抽象
// 先乘9，那肯定就是9的倍数。
// 取第一次digit，变成[9,18,,27...81]
// 再取一次，变成9，最后直接加n-9
// 也可以先digit，变成[1,81]
// 再乘99再digit，和都是18，就是n-18

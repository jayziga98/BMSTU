# Лабораторная работа ТиСД №1

## Входные данные

1) Вещественное число в форме +-m.nЕ+-K, где суммарная длина мантиссы (m+n) - до 30 значащих цифр, а величина порядка K - до 5 цифр

Для ввода допускаются символы [**+-0123456789.eE**].

Первый символ отвечает за знак мантиссы (может отсутсвовать).

Далее вводится мантисса до 30 символов(может отсутствовать). Точка в мантиссе может как присутствовать, так и отсутствовать (но только в единственном числе). После точки так же могут отсутствовать цифры (воспринимается как 0)

Символ экспоненты идет после мантиссы, или отсутсвует (в этом случае воспринимается как 0).

После него может идти знак экспоненты (+, - или отстутсвие)

Затем экспонента до 5 разрядов.

1) Число длиной до 30 десятичных цифр.

Первый символ отвечает за знак числа (может отсутсвовать).

Далее допускается ввод только цифр.

## Выходные данные

Произведение введеных чисел, в форме +-0.m1Е+-K1, где m1 - до 30 значащих цифр, а K1 - до 5 цифр.

## Позитивные тесты

1) Вещественное число (далее В. ч.) без знака мантиссы
2) В. ч. без мантиссы
3) В. ч. без точки
4) В. ч. без экспоненты
5) В. ч. без знака экспоненты
6) В. ч. без мантиссы и знака мантиссы
7) В. ч. без мантиссы, знака мантиссы и без точки
8) В. ч. без экспоненты и без точки
9) Максимальное В. ч. умножается на 1
10) В. ч. = 0
11) Целое число = 0
12) Мантисса - максимальное число, экспонента - отсутствует, целое число - максимальное число
13) 1E10 * 5
14) 1e2 * 100
15) Ведущие нули (30 штук)
16) 999E151 * 1234
17) 9E9000 * 9999999
18) -9 * -1
19) -9 * 1
20) 9 * -1
21) 0.09e-99999 * 100

## Негативные тесты

1) Мантисса и экспонента - состоят из 9
2) Экспонента переполняется при умножении
3) Пустой ввод
4) Слишком большая мантисса при вводе
5) Целое число не введено
6) Вещественное число не введено
7) -1EE * 1 Лишний знак экспоненты
8) 31231 -123E1 Второе число - вещественное
9) ++1Е1 - Лишний знак плюса вначале
10) Две точки 
11) Буква в вводе
12) Слишком большое целое
13) Переполнение в минус
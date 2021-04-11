# AbstractVM

Программа работает с данными, поступающими на вход в виде потока или файла(см. пример файлов в папке examples)
Выполняет действия, описанные в табл. ниже.

Эмулирует динамическую типизацию типов данных благодаря применению паттерна проектирования "Фабричный метод"

command | parameter | description
--- | --- | ---
exit |  | Stop to execute command queue and exit from AVM (necessary at the end of command queue)
print | | Asserts that the value at the top of the stack is an 8-bit integer
assert | @exception | check if @exception is true or not
push | @type(@value) | valid @type is int8, int16, int32, float, double; Pushes the @value at the top of the stack
pop | | Unstacks the value from the top of the stack
pop |	|	Unstacks the value from the top of the stack
add	|	|	Unstacks the first two values on the stack, adds them, then stacks the result
sub	|	|	Unstacks the first two values on the stack, subtracts them, then stacks the result
mul	|	|	Unstacks the first two values on the stack, multiplies them, then stacks the result
div	|	|	Unstacks the first two values on the stack, divides them, then stacks the result
mod	|	|	Unstacks the first two values on the stack, calculates the modulus, then stacks the result
;	|	|	All comments start with ';'

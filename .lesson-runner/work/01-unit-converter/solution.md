## Unit converter

The example repeats one pattern three times: store a Celsius value in a `double`, apply the formula, and print both. Each `printf` uses `%.1f`, which prints one digit after the point, so `212` appears as `212.0`.

The formula is written `celsius * 9.0 / 5.0 + 32.0`. The constants have a decimal point, so the arithmetic is done on `double` values. If they were written `9 / 5`, the division would be integer division and give 1, not 1.8, which is the mistake the arithmetic chapter warned about.

The extension asks what happens with an `int`. 37 Celsius is 98.6 Fahrenheit, so storing the result in an `int` keeps only 98, and the 0.6 is lost. The conversion itself didn't change; the type decided how much of the answer survived.

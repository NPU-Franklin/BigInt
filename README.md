# BigInt Class
----------------------------------------------------------------------------------------------------------

<img alt="GitHub" src="https://img.shields.io/github/license/NPU-Franklin/BigInt?style=for-the-badge">**Licensed under MIT License (see LICENSE for details)**

------------------------------------------------------------------------------------------------------------

​	In order to do mathematical operations on integer, which is beyond the range of long long type, I specifically designed this cpp BigInt Class based on vector container. It is capable of doing the following operations:(assume we have BigInt a,b;)

- `cin >> a;`To input an BigInt Class number from keyboard.

- `cout << a;`To output an BigInt Class number on the screen.

- `a + b`To add up two BigInt Class numbers.

- `a - b`To minus a BigInt Class number with another one.

- `a * b`To multiply a BigInt Class number with another one.

- `a / b`To divide a BigInt Class number with another one.

- `a % b`To calculate the modulo.

- `a.divide(b, <reserve digits>)`To do division and reserve any digits you want to.

- ```c++
  a += b; //equals to a = a + b
  a -= b; //equals to a = a - b
  a *= b; //equals to a = a * b
  a /= b; //equals to a = a / b
  a %= b; //equals to a = a % b
  ```

- `pow(a, <times>)`To calculate the power of a BigInt Class number.

- You can use the following operators to compare two BigInt Class numbers:

  ```c++
  a == b;
  a != b;
  a < b;
  a > b;
  a <= b;
  a >= b;
  ```

- `a.size()`To tell you how many digits are there in a BigInt Class number.

--------------------------------------------------------------------

  	*In order to do math more quickly I specially optimized the multiplication part using FFT arithmetic. Moreover, I use minus to replace division and come up with a way to reserve specific digits users want.*

----------------------------------------------------------------------------------------------------------

**<> with :heart: by NPU-Franklin**




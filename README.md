## Лабораторная работа 7

## Подготовка рабочей директории
```bash
root@LabPythonVM:/home/student/MaRLoR-64/workspace# export GITHUB_USERNAME=MaRLoR-64
root@LabPythonVM:/home/student/MaRLoR-64/workspace# alias gsed=sed
root@LabPythonVM:/home/student/MaRLoR-64/workspace# source scripts/activate
root@LabPythonVM:/home/student/MaRLoR-64/workspace# git clone https://github.com/${GITHUB_USERNAME}/lab06 projects/lab07
Клонирование в «projects/lab07»...
remote: Enumerating objects: 51, done.
remote: Counting objects: 100% (51/51), done.
remote: Compressing objects: 100% (29/29), done.
remote: Total 51 (delta 15), reused 47 (delta 14), pack-reused 0
Получение объектов: 100% (51/51), 13.13 КиБ | 292.00 КиБ/с, готово.
Определение изменений: 100% (15/15), готово.
root@LabPythonVM:/home/student/MaRLoR-64/workspace# cd projects/lab07
root@LabPythonVM:/home/student/MaRLoR-64/workspace/projects/lab07# git remote remove origin
root@LabPythonVM:/home/student/MaRLoR-64/workspace/projects/lab07# git remote add origin https://github.com/${GITHUB_USERNAME}/lab07
```
Настройка Hunter и сборка проекта
```bash
root@LabPythonVM:/home/student/MaRLoR-64/workspace/projects/lab07# mkdir -p cmake
root@LabPythonVM:/home/student/MaRLoR-64/workspace/projects/lab07# wget https://raw.githubusercontent.com/cpp-pm/gate/master/cmake/HunterGate.cmake -O cmake/HunterGate.cmake
--2025-04-17 22:29:05--  https://raw.githubusercontent.com/cpp-pm/gate/master/cmake/HunterGate.cmake
Распознаётся raw.githubusercontent.com (raw.githubusercontent.com)… 185.199.111.133, 185.199.108.133, 185.199.110.133, ...
Подключение к raw.githubusercontent.com (raw.githubusercontent.com)|185.199.111.133|:443... соединение установлено.
HTTP-запрос отправлен. Ожидание ответа… 200 OK
Длина: 17231 (17K) [text/plain]
Сохранение в: «cmake/HunterGate.cmake»

cmake/HunterGate.cm 100%[===================>]  16,83K  --.-KB/s    за 0,005s  

2025-04-17 22:29:05 (3,25 MB/s) - «cmake/HunterGate.cmake» сохранён [17231/17231]
root@LabPythonVM:/home/student/MaRLoR-64/workspace/projects/lab07# cmake -H. -B_builds -DBUILD_TESTS=ON
-- [hunter] Calculating Toolchain-SHA1
-- [hunter] Calculating Config-SHA1
-- [hunter] HUNTER_ROOT: /root/.hunter
-- [hunter] [ Hunter-ID: 23f1b5a | Toolchain-ID: 534d6c7 | Config-ID: bf2be25 ]
-- [hunter] GTEST_ROOT: /root/.hunter/_Base/23f1b5a/534d6c7/bf2be25/Install (ver.: 1.11.0)
-- Configuring done
-- Generating done
-- Build files have been written to: /home/student/MaRLoR-64/workspace/projects/lab07/_builds
root@LabPythonVM:/home/student/MaRLoR-64/workspace/projects/lab07# cmake --build _builds
[ 25%] Building CXX object CMakeFiles/print.dir/sources/print.cpp.o
[ 50%] Linking CXX static library libprint.a
[ 50%] Built target print
[ 75%] Building CXX object CMakeFiles/check.dir/tests/test1.cpp.o
[100%] Linking CXX executable check
[100%] Built target check
root@LabPythonVM:/home/student/MaRLoR-64/workspace/projects/lab07# cmake --build _builds --target test
Running tests...
Test project /home/student/MaRLoR-64/workspace/projects/lab07/_builds
    Start 1: check
1/1 Test #1: check ............................   Passed    0.00 sec

100% tests passed, 0 tests failed out of 1

Total Test time (real) =   0.00 sec
```
Настройка Hunter вручную
```bash
root@LabPythonVM:/home/student/MaRLoR-64/workspace/projects/lab07# git clone https://github.com/cpp-pm/hunter $HOME/projects/hunter
Клонирование в «/root/projects/hunter»...
remote: Enumerating objects: 53004, done.
remote: Counting objects: 100% (857/857), done.
remote: Compressing objects: 100% (230/230), done.
remote: Total 53004 (delta 679), reused 627 (delta 627), pack-reused 52147 (from 3)
Получение объектов: 100% (53004/53004), 13.80 МиБ | 24.79 МиБ/с, готово.
Определение изменений: 100% (33126/33126), готово.
root@LabPythonVM:/home/student/MaRLoR-64/workspace/projects/lab07# export HUNTER_ROOT=$HOME/projects/hunter
root@LabPythonVM:/home/student/MaRLoR-64/workspace/projects/lab07# rm -rf _builds
root@LabPythonVM:/home/student/MaRLoR-64/workspace/projects/lab07# gsed -i '/cmake_minimum_required(VERSION 3.4)/a\
include("cmake/HunterGate.cmake")\
HunterGate(
    URL "https://github.com/cpp-pm/hunter/archive/v0.23.308.tar.gz"
    SHA1 "23f1b5a0acffae50fda423388c843a8e7b6e1eb0"
)' CMakeLists.txt
root@LabPythonVM:/home/student/MaRLoR-64/workspace/projects/lab07# git rm -rf third-party/gtest
rm 'third-party/gtest'
root@LabPythonVM:/home/student/MaRLoR-64/workspace/projects/lab07# gsed -i '/set(PRINT_VERSION_STRING "v\${PRINT_VERSION}")/a\
hunter_add_package(GTest)\
find_package(GTest CONFIG REQUIRED)' CMakeLists.txt
root@LabPythonVM:/home/student/MaRLoR-64/workspace/projects/lab07# gsed -i 's/add_subdirectory(third-party\/gtest)//' CMakeLists.txt
root@LabPythonVM:/home/student/MaRLoR-64/workspace/projects/lab07# gsed -i 's/gtest_main/GTest::main/' CMakeLists.txt
```
Сборка проекта с использованием Hunter
```bash
root@LabPythonVM:/home/student/MaRLoR-64/workspace/projects/lab07# cmake -H. -B_builds -DBUILD_TESTS=ON
~~~~~~~
loading initial cache file /root/projects/hunter/_Base/xxxxxxx/534d6c7/d14f46d/Build/GTest/args.cmake
[100%] Completed 'GTest-Debug'
[100%] Built target GTest-Debug
-- [hunter] Build step successful (dir: /root/projects/hunter/_Base/xxxxxxx/534d6c7/d14f46d/Build/GTest)
-- [hunter] Cache saved: /root/projects/hunter/_Base/Cache/raw/16e18410a34066bd0176cf601b8920878ccf4037.tar.bz2
-- Found GTest: /root/projects/hunter/_Base/xxxxxxx/534d6c7/d14f46d/Install/lib/cmake/GTest/GTestConfig.cmake (found version "1.15.2")  
-- Configuring done
-- Generating done
-- Build files have been written to: /home/student/MaRLoR-64/workspace/projects/lab07/_builds
root@LabPythonVM:/home/student/MaRLoR-64/workspace/projects/lab07# cmake --build _builds
[ 25%] Building CXX object CMakeFiles/print.dir/sources/print.cpp.o
[ 50%] Linking CXX static library libprint.a
[ 50%] Built target print
[ 75%] Building CXX object CMakeFiles/check.dir/tests/test1.cpp.o
[100%] Linking CXX executable check
[100%] Built target check
root@LabPythonVM:/home/student/MaRLoR-64/workspace/projects/lab07# cmake --build _builds --target test
Running tests...
Test project /home/student/MaRLoR-64/workspace/projects/lab07/_builds
    Start 1: check
1/1 Test #1: check ............................   Passed    0.00 sec

100% tests passed, 0 tests failed out of 1

Total Test time (real) =   0.01 sec
```
Настройка Polly
```bash
root@LabPythonVM:/home/student/MaRLoR-64/workspace/projects/lab07# mkdir tools
root@LabPythonVM:/home/student/MaRLoR-64/workspace/projects/lab07# git submodule add https://github.com/ruslo/polly tools/polly
Клонирование в «/home/student/MaRLoR-64/workspace/projects/lab07/tools/polly»...
remote: Enumerating objects: 6578, done.
remote: Counting objects: 100% (32/32), done.
remote: Compressing objects: 100% (15/15), done.
remote: Total 6578 (delta 21), reused 20 (delta 17), pack-reused 6546 (from 1)
Получение объектов: 100% (6578/6578), 1.68 МиБ | 3.25 МиБ/с, готово.
Определение изменений: 100% (4551/4551), готово.
root@LabPythonVM:/home/student/MaRLoR-64/workspace/projects/lab07# tools/polly/bin/polly.py --test
Python version: 3.11
Build dir: /home/student/MaRLoR-64/workspace/projects/lab07/_builds/default
...
SUCCESS
root@LabPythonVM:/home/student/MaRLoR-64/workspace/projects/lab07# tools/polly/bin/polly.py --install
Python version: 3.11
Build dir: /home/student/MaRLoR-64/workspace/projects/lab07/_builds/default
...
SUCCESS
```


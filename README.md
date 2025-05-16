## Laboratory work VI

##Подготовка рабочей директории 
```bash
root@LabPythonVM:/home/student/Vladimir1209/workspace# git clone https://github.com/${GITHUB_USERNAME}/lab05 projects/lab06
Клонирование в «projects/lab06»...
remote: Enumerating objects: 42, done.
remote: Counting objects: 100% (42/42), done.
remote: Compressing objects: 100% (23/23), done.
remote: Total 42 (delta 11), reused 42 (delta 11), pack-reused 0 (from 0)
Получение объектов: 100% (42/42), 8.94 КиБ | 8.94 МиБ/с, готово.
Определение изменений: 100% (11/11), готово.
root@LabPythonVM:/home/student/Vladimir1209/workspace# cd projects/lab06
root@LabPythonVM:/home/student/Vladimir1209/workspace/projects/lab06# git remote remove origin
root@LabPythonVM:/home/student/Vladimir1209/workspace/projects/lab06# git remote add origin https://github.com/${GITHUB_USERNAME}/lab06
```
##Настройка Cmake
```bash
root@LabPythonVM:/home/student/Vladimir1209/workspace/projects/lab06# gsed -i '/project(print)/a\
> set(PRINT_VERSION_STRING "v\${PRINT_VERSION}")
' CMakeLists.txt
root@LabPythonVM:/home/student/Vladimir1209/workspace/projects/lab06# gsed -i '/project(print)/a\
> set(PRINT_VERSION\
  \${PRINT_VERSION_MAJOR}.\${PRINT_VERSION_MINOR}.\${PRINT_VERSION_PATCH}.\${PRINT_VERSION_TWEAK})
' CMakeLists.txt
root@LabPythonVM:/home/student/Vladimir1209/workspace/projects/lab06# gsed -i '/project(print)/a\
> set(PRINT_VERSION_TWEAK 0)
' CMakeLists.txt
root@LabPythonVM:/home/student/Vladimir1209/workspace/projects/lab06# gsed -i '/project(print)/a\
> set(PRINT_VERSION_TWEAK 0)
' CMakeLists.txt
root@LabPythonVM:/home/student/Vladimir1209/workspace/projects/lab06# gsed -i '/project(print)/a\
> set(PRINT_VERSION_PATCH 0)
' CMakeLists.txt
root@LabPythonVM:/home/student/Vladimir1209/workspace/projects/lab06# gsed -i '/project(print)/a\
> set(PRINT_VERSION_MINOR 1)
' CMakeLists.txt
root@LabPythonVM:/home/student/Vladimir1209/workspace/projects/lab06# gsed -i '/project(print)/a\
> set(PRINT_VERSION_MAJOR 0)
' CMakeLists.txt
root@LabPythonVM:/home/student/Vladimir1209/workspace/projects/lab06# git diff
diff --git a/CMakeLists.txt b/CMakeLists.txt
index 0753258..6798547 100644
--- a/CMakeLists.txt
+++ b/CMakeLists.txt
@@ -8,6 +8,14 @@ option(BUILD_TESTS "Build tests" OFF)
 option(BUILD_TESTS "Build tests" OFF)
 
 project(print)
+set(PRINT_VERSION_MAJOR 0)
+set(PRINT_VERSION_MINOR 1)
+set(PRINT_VERSION_PATCH 0)
+set(PRINT_VERSION_TWEAK 0)
+set(PRINT_VERSION_TWEAK 0)
+set(PRINT_VERSION
+  ${PRINT_VERSION_MAJOR}.${PRINT_VERSION_MINOR}.${PRINT_VERSION_PATCH}.${PRINT_VERSION_TWEAK})
+set(PRINT_VERSION_STRING "v${PRINT_VERSION}")
 
 add_library(print STATIC ${CMAKE_CURRENT_SOURCE_DIR}/sources/print.cpp)
 
root@LabPythonVM:/home/student/Vladimir1209/workspace/projects/lab06# touch DESCRIPTION && edit DESCRIPTION
root@LabPythonVM:/home/student/Vladimir1209/workspace/projects/lab06# touch ChangeLog.md
root@LabPythonVM:/home/student/Vladimir1209/workspace/projects/lab06# export DATE="`LANG=en_US date +'%a %b %d %Y'`"
root@LabPythonVM:/home/student/Vladimir1209/workspace/projects/lab06# cat > ChangeLog.md <<EOF
> * ${DATE} ${GITHUB_USERNAME} <${GITHUB_EMAIL}> 0.1.0.0
- Initial RPM release
> EOF
```
##Настройка CPack
```bash
root@LabPythonVM:/home/student/Vladimir1209/workspace/projects/lab06# cat > CPackConfig.cmake <<EOF
> include(InstallRequiredSystemLibraries)
> EOF
root@LabPythonVM:/home/student/Vladimir1209/workspace/projects/lab06# cat >> CPackConfig.cmake <<EOF
> set(CPACK_PACKAGE_CONTACT ${GITHUB_EMAIL})
set(CPACK_PACKAGE_VERSION_MAJOR \${PRINT_VERSION_MAJOR})
set(CPACK_PACKAGE_VERSION_MINOR \${PRINT_VERSION_MINOR})
set(CPACK_PACKAGE_VERSION_PATCH \${PRINT_VERSION_PATCH})
set(CPACK_PACKAGE_VERSION_TWEAK \${PRINT_VERSION_TWEAK})
set(CPACK_PACKAGE_VERSION \${PRINT_VERSION})
set(CPACK_PACKAGE_DESCRIPTION_FILE \${CMAKE_CURRENT_SOURCE_DIR}/DESCRIPTION)
set(CPACK_PACKAGE_DESCRIPTION_SUMMARY "static C++ library for printing")
> EOF
root@LabPythonVM:/home/student/Vladimir1209/workspace/projects/lab06# cat >> CPackConfig.cmake <<EOF
> set(CPACK_RESOURCE_FILE_LICENSE \${CMAKE_CURRENT_SOURCE_DIR}/LICENSE)
set(CPACK_RESOURCE_FILE_README \${CMAKE_CURRENT_SOURCE_DIR}/README.md)
> EOF
root@LabPythonVM:/home/student/Vladimir1209/workspace/projects/lab06# cat >> CPackConfig.cmake <<EOF
> set(CPACK_RPM_PACKAGE_NAME "print-devel")
set(CPACK_RPM_PACKAGE_LICENSE "MIT")
set(CPACK_RPM_PACKAGE_GROUP "print")
set(CPACK_RPM_CHANGELOG_FILE \${CMAKE_CURRENT_SOURCE_DIR}/ChangeLog.md)
set(CPACK_RPM_PACKAGE_RELEASE 1)
> EOF
root@LabPythonVM:/home/student/Vladimir1209/workspace/projects/lab06# cat >> CPackConfig.cmake <<EOF
> set(CPACK_DEBIAN_PACKAGE_NAME "libprint-dev")
set(CPACK_DEBIAN_PACKAGE_PREDEPENDS "cmake >= 3.0")
set(CPACK_DEBIAN_PACKAGE_RELEASE 1)
> EOF
root@LabPythonVM:/home/student/Vladimir1209/workspace/projects/lab06# cat >> CPackConfig.cmake <<EOF
root@LabPythonVM:/home/student/Vladimir1209/workspace/projects/lab06# cat >> CPackConfig.cmake <<EOF
> include(CPack)
> EOF
root@LabPythonVM:/home/student/Vladimir1209/workspace/projects/lab06# cat >> CMakeLists.txt <<EOF
> include(CPackConfig.cmake)
> EOF
root@LabPythonVM:/home/student/Vladimir1209/workspace/projects/lab06# gsed -i 's/lab05/lab06/g' README.md
root@LabPythonVM:/home/student/Vladimir1209/workspace/projects/lab06# git add .
root@LabPythonVM:/home/student/Vladimir1209/workspace/projects/lab06# git commit -m"added cpack config"
[master da99064] added cpack config
 5 files changed, 49 insertions(+), 17 deletions(-)
 create mode 100644 CPackConfig.cmake
 create mode 100644 ChangeLog.md
 create mode 100644 DESCRIPTION
```
##Сборка проекта
```bash
root@LabPythonVM:/home/student/Vladimir1209/workspace/projects/lab06# git tag v0.1.0.0
root@LabPythonVM:/home/student/Vladimir1209/workspace/projects/lab06# 
root@LabPythonVM:/home/student/Vladimir1209/workspace/projects/lab06# git push origin master --tags
Username for 'https://github.com': Vladimir1209
Password for 'https://Vladimir1209@github.com': 
remote: Repository not found.
fatal: repository 'https://github.com/Vladimir1209/lab06/' not found
root@LabPythonVM:/home/student/Vladimir1209/workspace/projects/lab06# git push origin master --tags
Username for 'https://github.com': Vladimir1209
Password for 'https://Vladimir1209@github.com': 
remote: Repository not found.
fatal: repository 'https://github.com/Vladimir1209/lab06/' not found
root@LabPythonVM:/home/student/Vladimir1209/workspace/projects/lab06# git push origin master --tags
Username for 'https://github.com': Vladimir1209
Password for 'https://Vladimir1209@github.com': 
Перечисление объектов: 48, готово.
Подсчет объектов: 100% (48/48), готово.
При сжатии изменений используется до 4 потоков
Сжатие объектов: 100% (29/29), готово.
Запись объектов: 100% (48/48), 9.96 КиБ | 9.96 МиБ/с, готово.
Всего 48 (изменений 14), повторно использовано 39 (изменений 11), повторно использовано пакетов 0
remote: Resolving deltas: 100% (14/14), done.
To https://github.com/Vladimir1209/lab06
 * [new branch]      master -> master
 * [new tag]         v0.1.0.0 -> v0.1.0.0
root@LabPythonVM:/home/student/Vladimir1209/workspace/projects/lab06# travis login --auto
root@LabPythonVM:/home/student/Vladimir1209/workspace/projects/lab06# travis enable
root@LabPythonVM:/home/student/Vladimir1209/workspace/projects/lab06# cmake -H. -B_build
-- Configuring done
-- Generating done
-- Build files have been written to: /home/student/Vladimir1209/workspace/projects/lab06/_build
root@LabPythonVM:/home/student/Vladimir1209/workspace/projects/lab06# cmake -H. -B_build
-- Configuring done
-- Generating done
-- Build files have been written to: /home/student/Vladimir1209/workspace/projects/lab06/_build
root@LabPythonVM:/home/student/Vladimir1209/workspace/projects/lab06# cmake --build _build
[ 50%] Building CXX object CMakeFiles/print.dir/sources/print.cpp.o
[100%] Linking CXX static library libprint.a
[100%] Built target print
root@LabPythonVM:/home/student/Vladimir1209/workspace/projects/lab06# cd _build
root@LabPythonVM:/home/student/Vladimir1209/workspace/projects/lab06/_build# cpack -G "TGZ"
CPack: Create package using TGZ
CPack: Install projects
CPack: - Run preinstall target for: print
CPack: - Install project: print []
CPack: Create package
CPack: - package: /home/student/Vladimir1209/workspace/projects/lab06/_build/print-0.1.0.0-Linux.tar.gz generated.
root@LabPythonVM:/home/student/Vladimir1209/workspace/projects/lab06/_build# cd ..
root@LabPythonVM:/home/student/Vladimir1209/workspace/projects/lab06# cmake -H. -B_build -DCPACK_GENERATOR="TGZ"
-- Configuring done
-- Generating done
-- Build files have been written to: /home/student/Vladimir1209/workspace/projects/lab06/_build
root@LabPythonVM:/home/student/Vladimir1209/workspace/projects/lab06# cmake --build _build --target package
[100%] Built target print
Run CPack packaging tool...
CPack: Create package using TGZ
CPack: Install projects
CPack: - Run preinstall target for: print
CPack: - Install project: print []
CPack: Create package
CPack: - package: /home/student/Vladimir1209/workspace/projects/lab06/_build/print-0.1.0.0-Linux.tar.gz generated.
root@LabPythonVM:/home/student/Vladimir1209/workspace/projects/lab06# mkdir artifacts
root@LabPythonVM:/home/student/Vladimir1209/workspace/projects/lab06# mv _build/*.tar.gz artifacts
root@LabPythonVM:/home/student/Vladimir1209/workspace/projects/lab06# tree artifacts
artifacts
└── print-0.1.0.0-Linux.tar.gz

1 directory, 1 file
root@LabPythonVM:/home/student/Vladimir1209/workspace/projects/lab06# popd
/home/student/Vladimir1209/workspace
root@LabPythonVM:/home/student/Vladimir1209/workspace# export LAB_NUMBER=06
root@LabPythonVM:/home/student/Vladimir1209/workspace# git clone https://github.com/tp-labs/lab${LAB_NUMBER} tasks/lab${LAB_NUMBER}
Клонирование в «tasks/lab06»...
remote: Enumerating objects: 117, done.
remote: Counting objects: 100% (37/37), done.
remote: Compressing objects: 100% (4/4), done.
remote: Total 117 (delta 35), reused 33 (delta 33), pack-reused 80 (from 1)
Получение объектов: 100% (117/117), 1.33 МиБ | 5.63 МиБ/с, готово.
Определение изменений: 100% (36/36), готово.
```
##Report
```bash
root@LabPythonVM:/home/student/Vladimir1209/workspace/projects/lab06# popd
/home/student/Vladimir1209/workspace
root@LabPythonVM:/home/student/Vladimir1209/workspace# export LAB_NUMBER=06
root@LabPythonVM:/home/student/Vladimir1209/workspace# git clone https://github.com/tp-labs/lab${LAB_NUMBER} tasks/lab${LAB_NUMBER}
Клонирование в «tasks/lab06»...
remote: Enumerating objects: 117, done.
remote: Counting objects: 100% (37/37), done.
remote: Compressing objects: 100% (4/4), done.
remote: Total 117 (delta 35), reused 33 (delta 33), pack-reused 80 (from 1)
Получение объектов: 100% (117/117), 1.33 МиБ | 5.63 МиБ/с, готово.
Определение изменений: 100% (36/36), готово.
root@LabPythonVM:/home/student/Vladimir1209/workspace# mkdir reports/lab${LAB_NUMBER}
root@LabPythonVM:/home/student/Vladimir1209/workspace# cp tasks/lab${LAB_NUMBER}/README.md reports/lab${LAB_NUMBER}/REPORT.md
root@LabPythonVM:/home/student/Vladimir1209/workspace# cd reports/lab${LAB_NUMBER}
root@LabPythonVM:/home/student/Vladimir1209/workspace/reports/lab06# edit REPORT.md
```

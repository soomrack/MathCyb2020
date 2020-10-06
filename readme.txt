Блокчейн.
Практические занятия.

Требуется использование библиотек OpenSSL и Boost.

Установка Boost (mingw):
1. Скачать файл boost_1_73_0.zip (Windows) или boost_1_73_0.tar.bz2 (linux)
   с официального сайта boost https://www.boost.org/users/history/version_1_73_0.html
2. Распаковать архив в C:\Program Files\boost\boost_1_73_0 для Windows или
   /usr/local/boost_1_73_0 для linux
3. Библиотека скомпилируется и будет найдена средствами cmake

Установка Openssl (mingw):
1. Так как вся команда использует Anaconda3 в учебных целях, эта библиотека уже
   скачана и может быть просто найдена cmake
2. В противном случае эта библиотека поставляется вместе с git, так что нужно
   запустить C:\Program Files\Git\usr\bin\openssl.exe


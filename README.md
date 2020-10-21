# SPUAsm
## Транслятор assembly-подобного кода и SPU-исполнитель
В данном проекте реализован транслятор кода в неравномерный байткод, дизассемблер для байткода, исполнитель байткода (Soft Processor Unit).

В дополнение, присутствует анализатор кода, проверяющий синтаксические ошибки и выбрасывающий отчет в clang формате. Поэтому, XCode и другие IDE поддерживающие clang подсвечивают неверные выражения, отображают комментарии.

Во время трансляции генерируется .lst файл, содержащий информацию о трансляции, на каком offset бинарника какая команда и тд. Все доступно в примерах.

<img src="https://github.com/AlexRoar/MIPTProjects_1sem/raw/master/SoftProcessorUnit/Images/Снимок%20экрана%202020-10-16%20в%2000.20.38.png">
<img height="100px" src="https://github.com/AlexRoar/MIPTProjects_1sem/raw/master/SoftProcessorUnit/Images/Снимок%20экрана%202020-10-16%20в%2000.21.56.png">

- [Основной код транслятора](https://github.com/AlexRoar/MIPTProjects_1sem/blob/master/SoftProcessorUnit/SoftProcessorUnit/Assembly/SPUAssembly.cpp)
- [Основной код дизассемблера](https://github.com/AlexRoar/MIPTProjects_1sem/blob/master/SoftProcessorUnit/SoftProcessorUnit/Disassembly/SPUDisAssembly.cpp)
- [Основной код SPU](https://github.com/AlexRoar/MIPTProjects_1sem/blob/master/SoftProcessorUnit/SoftProcessorUnit/SPU/SPU.cpp)
- [Примеры](https://github.com/AlexRoar/MIPTProjects_1sem/tree/master/SPUAsm/SPUAsm)

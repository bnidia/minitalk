# minitalk (Complexity 50 hours)
<img src="https://badge42.vercel.app/api/v2/cl3enoo9k004009muhk5a94tj/project/2528987" alt="bnidia's 42 minitalk Score" />

### The purpose of this project is to code a small data exchange program using UNIX signals. It is an introductory project for the bigger UNIX projects that will appear later on in the cursus.
This project is dedicated to signal transmission in the operating system. We were asked to write two client and server programs that send text to each other using binary signals. It was interesting to study atomicity and the special variable sig_atomic_t

![minitalk demontration](https://github.com/bnidia/minitalk/blob/master/minitalk_demonstration.gif)

### Целью этого проекта является кодирование небольшой программы обмена данными с использованием сигналов UNIX. Это вводный проект для более крупных проектов UNIX, которые появятся позже на курсе.
Этот проект посвящен передаче сигналов в операционной системе. Нам было предложено написать две программы клиент и сервер, которые пересылают друг другу текст с помощью бинарных сигналов. Интересно было изучить атомарность и специальную переменную sig_atomic_t

### How to build and run
Download to your computer, go to the directory minitalk, compile with make and then run client and server.
client needs pid of server, and then text. 
```
git clone https://github.com/bnidia/minitalk.git
cd minitalk
make
./fdf ./maps/mars.fdf
```

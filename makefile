all: exec

exec: main.o Post.o Notification.o User.o SocialMedia.o
	g++ main.o Post.o Notification.o User.o SocialMedia.o -o exec

main.o: main.cpp User.hpp SocialMedia.hpp
	g++ -c main.cpp -o main.o

User.o: User.cpp User.hpp DynamicList.hpp Post.hpp Notification.hpp
	g++ -c User.cpp -o User.o

SocialMedia.o: SocialMedia.cpp SocialMedia.hpp User.hpp DynamicList.hpp
	g++ -c SocialMedia.cpp -o SocialMedia.o

Post.o: Post.cpp Post.hpp User.hpp
	g++ -c Post.cpp -o Post.o

Notification.o: Notification.cpp Notification.hpp User.hpp
	g++ -c Notification.cpp -o Notification.o

run: all
	./exec initial_users.txt

clean:
	rm -f *.o exec

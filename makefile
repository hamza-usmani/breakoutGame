# Add $(MAC_OPT) to the compile line for macOS 
# (should be ignored by Linux, set to nothing if causing problems)
MAC_OPT = -I/opt/X11/include 

all:
	@echo "Compiling..."
	g++ -std=c++14 -o Breakout main.cpp SplashScreen.cpp Ball.cpp Grid.cpp Paddle.cpp ChooseType.cpp -L/opt/X11/lib -lX11 -lstdc++ $(MAC_OPT)

run: all
	@echo "Running..."
	./Breakout

clean:
	-rm Breakout

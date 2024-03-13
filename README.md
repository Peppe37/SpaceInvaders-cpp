# Compile

To compile the main.exe go to the default workspace path and run:

```bash
g++ .\src\main.cpp -o .\lib\SFML-mingw32\bin\main.exe -I{YOUR LIB SFML PATH}\include -L{YOUR LIB SFML PATH}\lib -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio -lopengl32 -lfreetype -lwinmm -lgdi32
```

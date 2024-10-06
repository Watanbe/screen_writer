# Nome do executável
TARGET = janela

# Compilador
CXX = g++

# Flags de compilação
CXXFLAGS = -std=c++11 -I /usr/include/SFML

# Bibliotecas SFML
LIBS = -lsfml-graphics -lsfml-window -lsfml-system 

# Arquivos fonte
SOURCES = main.cpp
OBJECTS = $(SOURCES:.cpp=.o)

# Regra padrão
all: $(TARGET)

# Como compilar o executável
$(TARGET): $(OBJECTS)
	$(CXX) -o $@ $^ $(LIBS)

# Como compilar os arquivos objeto
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $<

# Limpar os arquivos gerados
clean:
	rm -f $(OBJECTS) $(TARGET)

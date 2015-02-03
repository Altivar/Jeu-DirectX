#include "GameState.h"
#include <conio.h>

// memory leaks
#include <crtdbg.h>
#ifdef _DEBUG 
  #define new new( _CLIENT_BLOCK, __FILE__, __LINE__)
#endif // _DEBUG

GameState::GameState(void)
{

}


GameState::~GameState(void)
{

}
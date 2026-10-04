///                                                                           
/// Langulus test module                                                      
/// Copyright (c) 2016 Dimo Markov <team@langulus.com>                        
/// Part of the Langulus framework, see https://langulus.com                  
///                                                                           
/// SPDX-License-Identifier: GPL-3.0-or-later                                 
///                                                                           
#include "Main.hpp"

LANGULUS_DEFINE_MODULE(
   TestModule, 1, "TestModule", "Just some module for testing", "",
   SomeCategory, SomeReflectedType1, SomeReflectedType2
)

int main(int, char**) {
	return 0;
}

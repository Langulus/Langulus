///                                                                           
/// Langulus::Framework                                                       
/// Copyright(C) 2016 Dimo Markov <langulusteam@gmail.com>                    
///                                                                           
/// Distributed under GNU General Public License v3+                          
/// See LICENSE file, or https://www.gnu.org/licenses                         
///                                                                           
#include "Main.hpp"

LANGULUS_DEFINE_MODULE(
   TestModule, 1, "TestModule", "Just some module for testing", "",
   SomeCategory, SomeReflectedType1, SomeReflectedType2
)

int main(int, char**) {
	return 0;
}

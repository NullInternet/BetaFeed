/*Copyright 2017 Paul Salvador Inventado

Licensed under the Apache License, Version 2.0 (the "License");
you may not use this file except in compliance with the License.
You may obtain a copy of the License at

    http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software
distributed under the License is distributed on an "AS IS" BASIS,
WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
See the License for the specific language governing permissions and
limitations under the License.
*/

#include "fbpastpost.h"
#include <iostream>

//Edit this file, replacing quoted .glade and window with those found in BetaFeed
int main(){
	GladeAppManager gapManager("BetaFeed_GUI.glade");
	LoginController lc("start_window");
	gapManager.addViewController(&lc, true);
	PostController pc("posts_window");
	gapManager.addViewController(&pc);
	//New reaction controller for reactions to individual posts
	ReactionController rc("reaction_window");
	gapManager.addViewController(&rc);
	gapManager.start();
}


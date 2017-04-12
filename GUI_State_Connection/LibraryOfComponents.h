/*
  ==============================================================================

    LibraryOfComponents.h
    Created: 7 Apr 2017 4:10:08pm
    Author:  admin

  ==============================================================================
*/
#include "GUIComponent.h"
#include "MainComponent.h"

#ifndef LIBRARYOFCOMPONENTS_H_INCLUDED
#define LIBRARYOFCOMPONENTS_H_INCLUDED

class LibraryOfComponents {
public:
	//LibraryOfComponents();
	LibraryOfComponents() {
		//do nothing
	}
	//LibraryOfComponents(GUIComponent* guiComponent, MainContentComponent* mainContentComponent);
	
	//void setGUIComponent(GUIComponent guiComponent);
	//void setMainContentComponent(MainContentComponent &mainContentComponent);
	static GUIComponent* guiComponent;
	static MainContentComponent* mainContentComponent;
	LibraryOfComponents(GUIComponent* guiComp, MainContentComponent* mainComp) {
		//guiComponent = NULL;
		//mainContentComponent = NULL;
		guiComponent = guiComp;
		mainContentComponent = mainComp;
	}
};

GUIComponent* LibraryOfComponents::guiComponent = NULL;
MainContentComponent* LibraryOfComponents::mainContentComponent = NULL;



#endif  // LIBRARYOFCOMPONENTS_H_INCLUDED

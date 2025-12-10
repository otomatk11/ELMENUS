


cmake_minimum_required(VERSION 4.1)
project(ELMenus VERSION 1.0 LANGUAGES CXX)

set( SOURCES
	Status.cpp
	FoodItem.cpp
	User.cpp
	Customer.cpp
	DliveryDriver.cpp
	Order.cpp
	FileData.cpp
	Type.cpp
)

add_executable(elmenus)
target_sources(elmenus PRIVATE main.cpp ${SOURCES})

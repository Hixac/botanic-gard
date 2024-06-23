#if defined(_WIN32)
#pragma once

#include <Windows.h>

#include <string>
#include <fstream>
#include <iostream>

#include <cassert>

namespace Utils {

	static std::wstring s2ws(const std::string& str)
	{
		int size_needed = MultiByteToWideChar(CP_UTF8, 0, &str[0], (int)str.size(), NULL, 0);
		std::wstring wstrTo(size_needed, 0);
		MultiByteToWideChar(CP_UTF8, 0, &str[0], (int)str.size(), &wstrTo[0], size_needed);
		return wstrTo;
	}

	static void SaveStateWindows(std::string data)
	{
		char* appdata = std::getenv("APPDATA");

		std::string path =  std::string(appdata) + "\\Ботанический сад\\";
		std::cout << "Appdata folder: " << path << std::endl;
		
		if (CreateDirectory(path.c_str(), NULL)) {
			std::cout << "Folder has created!" << std::endl;
		} else {
			std::cout << "Folder already existing" << std::endl;
		}

		std::ofstream out(path + "config.ini", std::ios::trunc);
		assert(out && "File didn't opened!");

		out << data;
	}

	static std::string GetStateWindows()
	{
		char* appdata = std::getenv("APPDATA");

		std::string path = std::string(appdata) + "\\Ботанический сад\\";
		std::cout << "Appdata folder: " << path << std::endl;

		std::ifstream in(path + "config.ini");
		if (!in) {
			SaveStateWindows("");

			in.clear();
			in.open(path + "config.ini");
		}

		std::string data;
		std::getline(in, data); // change

		return data;
	}

}

#endif
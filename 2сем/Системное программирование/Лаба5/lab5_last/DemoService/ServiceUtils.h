#pragma once
#include <string>
#include <fstream>

bool LoadConfig(const char* configPath);
void LogMessage(const std::string& message);
void LogLastError(const char* context);
void CopyFilesOnce();
std::string GetCurrentTimeStr();
extern std::ofstream logFile; 
extern int intervalMinutes; 
#pragma once

int doFile(const char *fileName);

void usage();

int parseAlg(const char *param, const unsigned int pSize);

int parseWidth(const char *param, const unsigned int pSize);

int parseDigestWidth(const char *param, const unsigned int pSize);

int parseOption(const char *param, const unsigned int pSize);

void parseParameter(const char *param);

void parseCommandLine(const int argc, char* argv[]);

void parseCommandLine(const int argc, char* argv[], unsigned int, unsigned int);

void parseCommandLineOnlyNums(const int argc, char* argv[]);

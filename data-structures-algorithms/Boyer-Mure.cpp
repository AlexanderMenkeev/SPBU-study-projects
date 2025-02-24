//Задание номер 10 по алгоритмам и структурам данных.
//Реализация алгоритма поиска подстрок

//#include <iostream>
//#include <fstream>
//#include <string>
//#include <vector>
//
//void buildTableOfBadCharacters(std::string patern, int* pos)
//{
//	for (int i = 0; i < 58; i++)
//		pos[i] = -1;
//
//	for (int i = 0; i < patern.length(); i++)
//		pos[patern[i] - 65] = i;
//}
//
//void buildTableOfGoodSufs(std::string patern, int* suf)
//{
//	int m = patern.length();
//	////for (int i = 0; i < m; i++)
//		suf[i] = -1;
//
//	int i = 0, j = 0;
//	for (int x = 0; x <= m - 2; x++)
//	{
//		i = x;
//		j = m - 1;
//		while (i >= 0 && patern[i] == patern[j])
//		{
//			suf[j] = i;
//			i--;
//			j--;
//		}
//	}
//}
//
//void preprocess_strong_suffix(int* shift, int* bpos,
//	char* pat, int m)
//{
//	int i = m, j = m + 1;
//	bpos[i] = j;
//	while (i > 0)
//	{
//		while (j <= m && pat[i - 1] != pat[j - 1])
//		{
//			if (shift[j] == 0)
//				shift[j] = j - i;
//			j = bpos[j];
//		}
//		i--; j--;
//		bpos[i] = j;
//	}
//}
//
//int find1(std::string mainString, std::string patern, int* pos, int* suf, int& ind)
//{
//	int n = mainString.length();
//	int m = patern.length();
//	int i = ind + 1; int j;
//	while (i <= n - m)
//	{
//		j = m - 1;
//		while (mainString[i + j] == patern[j])
//		{
//			j--;
//			if (j < 0)
//				return i;
//		}
//		i += std::max(j - pos[mainString[i + j] - 65], 1);
//	}
//	return -1;
//}
//
//int find2(std::string mainString, std::string patern, int* pos, int* suf, int& ind)
//{
//	int n = mainString.length();
//	int m = patern.length();
//	int i = ind + 1 + m - 1; int j;
//	while (i < n)
//	{
//		j = m - 1;
//		while (mainString[i] == patern[j])
//		{
//			j--; i--;
//			if (j < 0)
//				return i + 1;
//		}
//		i += m - j + 1 - suf[j + 1];
//	}
//	return -1;
//}
//
//
//int find(std::string mainString, std::string patern, int* pos, int* suf, int& ind)
//{
//	int n = mainString.length();
//	int m = patern.length();
//	int i = ind + 1 + m - 1; int j;
//	while (i < n)
//	{
//		j = m - 1;
//		while (mainString[i] == patern[j])
//		{
//			j--; i--;
//			if (j == 0)
//				return i;
//		}
//		i += std::max(j - pos[mainString[i + j] - 65],
//						j + 1 - suf[j + 1]);
//	}
//	return -1;
//}
//
//
//int main(int argc, char* argv[])
//{
//	std::ifstream inFile("C:\\Users\\Александр\\github-classroom\\amcp-pit\\task10-fastsubstr-AlexanderMenkeev\\tests\\in\\input1.txt");
//	if (!inFile) return 2;
//	std::ofstream outFile("C:\\Users\\Александр\\github-classroom\\amcp-pit\\task10-fastsubstr-AlexanderMenkeev\\tests\\out\\output1.txt");
//	if (!outFile) return 3;
//
//	std::string mainString;
//	std::string patern;
//	std::getline(inFile, patern);
//	std::getline(inFile, mainString);
//	int sizeOfStr = mainString.length();
//	int sizeOfPatern = patern.length();
//
//	int pos[58];
//	int* suf = new int[sizeOfPatern];
//	buildTableOfBadCharacters(patern, pos);
//	buildTableOfGoodSufs(patern, suf);
//
//	std::cout << mainString << std::endl;
//	std::cout << patern << std::endl;
//
//	for (int i = 0; i < sizeOfPatern; i++)
//		std::cout << pos[patern[i] - 65] << " ";
//	std::cout << '\n';
//	for (int i = 0; i < sizeOfPatern; i++)
//		std::cout << suf[i] << " ";
//	std::cout << '\n';
//
//
//	int ind = -1;
//	std::vector<int> result;
//	while (1)
//	{
//		ind = find2(mainString, patern, pos, suf, ind);
//		if (ind == -1)
//			break;
//		else
//		{
//			result.push_back(ind);
//			std::cout << "ind = " << ind + 1 << std::endl;
//		}
//	}
//
//	outFile << result.size() << '\n';
//	for (int i = 0; i < result.size(); i++)
//	{
//		if (i != 0)
//			outFile << " ";
//		outFile << result[i] + 1;
//	}
//
//	
//	std::cout << "Time: " << clock();
//	delete[] suf;
//	inFile.close();
//	outFile.close();
//	return 0;
//}
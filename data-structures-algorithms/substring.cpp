////Задание номер 10 по алгоритмам и структурам данных.
////Реализация алгоритма поиска подстрок
//
//#include <iostream>
//#include <fstream>
//#include <string>
//#include <vector>
//
//void buildP(std::string t, int* p)
//{
//	p[0] = -1;
//	p[1] = 0;
//	int i = 1; int j = 0;
//	while (i < t.length())
//	{
//		if (t[i] == t[j])
//		{
//			p[i + 1] = j + 1;
//			++i; ++j;
//		}
//		else
//		{
//			if (j > 0)
//				j = p[j];
//			else
//			{
//				p[i + 1] = 0;
//				++i;
//			}
//		}
//	}
//}
//
//int find(std::string mainString, std::string patern, int* p, int& k)
//{
//	int i = k + 1; int j = 0;
//	while (i < mainString.length() && j < patern.length())
//	{
//		if (mainString[i] == patern[j])
//		{
//			++i; ++j;
//		}
//		else
//		{
//			if (j > 0)
//				j = p[j];
//			else
//				++i;
//		}
//	}
//	if (j == patern.length())
//		return i - patern.length();
//	else
//		return -1;
//}
//
//
//int main(int argc, char* argv[])
//{
//	std::ifstream inFile("C:\\Users\\Александр\\github-classroom\\amcp-pit\\task10-fastsubstr-AlexanderMenkeev\\tests\\in\\input3.txt");
//	if (!inFile) return 2;
//	std::ofstream outFile("C:\\Users\\Александр\\github-classroom\\amcp-pit\\task10-fastsubstr-AlexanderMenkeev\\tests\\out\\output3.txt");
//	if (!outFile) return 3;
//	
//	std::string mainString;
//	std::string patern;
//	std::getline(inFile, patern);
//	std::getline(inFile, mainString);
//	int size = mainString.length();
//	int* p = new int[size+1];
//	buildP(mainString, p);
//
//	std::cout << patern << std::endl;
//	std::cout << mainString << std::endl;
//	for (int i = 1; i < size+1; i++)
//		std::cout << p[i];
//	std::cout << std::endl;
//
//	int ind = -1;
//	std::vector<int> result;
//	while (1)
//	{
//		ind = find(mainString, patern, p, ind);
//		if (ind == -1)
//			break;
//		else
//		{
//			result.push_back(ind);
//			std::cout << "ind = " << ind+1 << std::endl;
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
//	std::cout << "Time: " << clock();
//	delete[] p;
//	inFile.close();
//	outFile.close();
//	return 0;
//}
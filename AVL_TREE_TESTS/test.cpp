#include "pch.h"
#include "../AVL_TREE/avl_tree.h"
#include <string>
#include <map>

using namespace std;
using namespace avl_tree_map;
TEST(Constructor, Empty)
{
	avl_tree<int, int> tree;
	EXPECT_TRUE(tree.empty());
}

TEST(Constructor, Copy)
{
	avl_tree<char, string> tree;
	tree.insert(make_pair('0', "abc"));
	tree.insert(make_pair('1', "zxc"));
	tree.insert(make_pair('2', "klj"));

	avl_tree<char, string> copy(tree);

	EXPECT_TRUE(copy['0'] == "abc");
	EXPECT_TRUE(tree.size() == copy.size());
}

TEST(Constructor, MoveCopy)
{
	avl_tree<char, string> tree(
		avl_tree<char, string>({
			make_pair('0', "abc"),
			make_pair('1', "zxc"),
			make_pair('2', "klj")
		})
	);

	EXPECT_TRUE(tree['0'] == "abc");
	EXPECT_TRUE(tree['1'] == "zxc");
	EXPECT_TRUE(tree['2'] == "klj");
	EXPECT_TRUE(tree.size() == 3);
}

TEST(Iterator, Next)
{
	avl_tree<char, string> tree;
	tree.insert(make_pair('0', "abc"));
	tree.insert(make_pair('1', "zxc"));
	tree.insert(make_pair('2', "klj"));

	auto iterator = tree.begin();
	EXPECT_EQ("abc", iterator++->second);
	EXPECT_EQ("zxc", iterator++->second);
	EXPECT_EQ("klj", iterator->second);
}

TEST(ConstIterator, Next)
{
	avl_tree<char, string> tree;
	tree.insert(make_pair('0', "abc"));
	tree.insert(make_pair('1', "zxc"));
	tree.insert(make_pair('2', "klj"));

	auto iterator = tree.cbegin();
	EXPECT_EQ("abc", iterator++->second);
	EXPECT_EQ("zxc", iterator++->second);
	EXPECT_EQ("klj", iterator->second);
}

TEST(Iterator, CopyToAnotherContainer)
{
	avl_tree<int, char> tree({
		make_pair(1, '1'),
		make_pair(2, '2'),
		make_pair(3, '!')
	});
	map<int, char> map(tree.begin(), tree.end());

	EXPECT_TRUE(map[1] == '1');
	EXPECT_TRUE(map[2] == '2');
	EXPECT_TRUE(map[3] == '!');
}


TEST(Functions, MergeLValue)
{
	avl_tree<char, string> tree1;
	tree1.insert(make_pair('0', "abc"));
	tree1.insert(make_pair('1', "zxc"));
	tree1.insert(make_pair('2', "klj"));

	avl_tree<char, string> tree2;
	tree2.insert(make_pair('3', "654"));
	tree2.insert(make_pair('4', "678"));
	tree2.insert(make_pair('2', "10001`3812"));

	tree1.merge(tree2);

	EXPECT_TRUE(tree1['3'] == "654");
	EXPECT_TRUE(tree1['4'] == "678");
	EXPECT_TRUE(tree1['2'] == "klj");
	EXPECT_TRUE(tree2['2'] == "10001`3812");
	EXPECT_TRUE(tree2.size() == 1);
	EXPECT_TRUE(tree1.size() == 5);
}

TEST(Functions, Insesrt)
{
	avl_tree<string, int32_t> tree;

	pair<string, int> p = make_pair("123", 123);
	auto res = tree.insert(p);
	EXPECT_EQ(123, res.first->second);
	EXPECT_TRUE(res.second);
	pair<string, int> p1 = make_pair("123", 321);
	auto res1 = tree.insert(p1);
	EXPECT_TRUE(!res1.second);

	tree.insert(make_pair("321", 123));
	EXPECT_EQ(tree["321"], 123);
}

TEST(Functions, InsesrtByIterators)
{
	vector<pair<char, string>> vec = {
		make_pair('0', "123"),
		make_pair('1', "234"),
		make_pair('2', "345")
	};
	avl_tree<char, string> tree;
	tree.insert(vec.begin(), vec.end());

	EXPECT_TRUE(tree['0'] == "123");
	EXPECT_TRUE(tree.size() == 3);
}

TEST(Functions, GetAndInsertByBraces)
{
	avl_tree<size_t, size_t> tree;
	tree[0] = 123;
	EXPECT_EQ(tree[0], 123);
	EXPECT_EQ(tree[1], 0);
	tree[1] = 1000;
	EXPECT_EQ(tree[1], 1000);
}

TEST(Functions, Contains)
{
	avl_tree<size_t, size_t> tree;
	EXPECT_FALSE(tree.contains(0));
	tree.insert(make_pair(0, 123));
	EXPECT_TRUE(tree.contains(0));
}

TEST(Functions, Size)
{
	avl_tree<size_t, size_t> tree;
	EXPECT_EQ(tree.size(), 0);
	for (int i = 0; i < 10; ++i)
	{
		tree.insert(make_pair(i, i));
	}
	tree.erase(0);
	tree.erase(5);
	EXPECT_EQ(tree.size(), 8);
}

TEST(Functions, Find)
{
	avl_tree<size_t, size_t> tree;
	EXPECT_TRUE(tree.find(0) == tree.end());
	tree.insert(make_pair(0, 123));
	EXPECT_TRUE(tree.find(0)->second == 123);
}

TEST(Functions, EraseByItrerator)
{
	avl_tree<string, int32_t> tree;
	pair<string, int> p = make_pair("123", 123);
	tree.insert(p);
	auto iterator = tree.find("123");
	EXPECT_TRUE(iterator->second == 123);
	auto res = tree.erase(iterator);
	EXPECT_TRUE(res == tree.end());
}

TEST(Functions, EraseByKey)
{
	avl_tree<string, int32_t> tree;
	pair<string, int> p = make_pair("123", 123);
	tree.insert(p);
	auto res = tree.erase("123");
	EXPECT_TRUE(res == 1);
	res = tree.erase("123");
	EXPECT_TRUE(res == 0);
}

TEST(Functions, EraseByIterators)
{
	avl_tree<char, string> tree;
	tree.insert(make_pair('0', "abc"));
	tree.insert(make_pair('1', "zxc"));
	tree.insert(make_pair('2', "klj"));

	tree.erase(tree.cbegin(), tree.cend());
	EXPECT_TRUE(tree.find('0') == tree.end());
	EXPECT_TRUE(tree.empty());
}

TEST(Functions, Clear)
{
	avl_tree<char, string> tree;
	tree.insert(make_pair('0', "abc"));
	tree.insert(make_pair('1', "zxc"));
	tree.insert(make_pair('2', "klj"));

	EXPECT_TRUE(tree.find('2')->second == "klj");
	EXPECT_TRUE(tree.size() == 3);

	tree.clear();
	EXPECT_TRUE(tree.find('0') == tree.end());
	EXPECT_TRUE(tree.find('1') == tree.end());
	EXPECT_TRUE(tree.find('2') == tree.end());
	EXPECT_TRUE(tree.size() == 0);
	EXPECT_TRUE(tree.empty());
}

TEST(Functions, InsertOrAssign)
{
	avl_tree<string, int32_t> tree;
	string key = "123";
	auto res1 = tree.insert_or_assign<int32_t>(key, 123);
	EXPECT_TRUE(res1.second == true);
	auto res2 = tree.insert_or_assign<int32_t>(key, 666);
	EXPECT_TRUE(res2.second == false);
	EXPECT_TRUE(tree[key] == 666);
}

TEST(Functions, InsertOrAssign2)
{
	avl_tree<string, int32_t> tree;
	auto res1 = tree.insert_or_assign<int32_t>("123", 123);
	EXPECT_TRUE(res1.second == true);
	auto res2 = tree.insert_or_assign<int32_t>("123", 666);
	EXPECT_TRUE(res2.second == false);
	EXPECT_TRUE(tree["123"] == 666);
}

TEST(Functions, BeginEnd)
{
	avl_tree<string, int32_t> tree;
	EXPECT_TRUE(tree.begin() == tree.end());
	EXPECT_TRUE(tree.cbegin() == tree.cend());
}

TEST(Functions, TryEmplace)
{
	avl_tree<char, string> tree;
	tree.try_emplace('a', "123");

	EXPECT_TRUE(tree['a'] == "123");
	EXPECT_FALSE(tree.try_emplace('a', "321").second);

	char key = 'b';
	EXPECT_TRUE(tree.try_emplace(key, "321").second);
	EXPECT_TRUE(tree[key] == "321");
}

TEST(Functions, Emplace)
{
	avl_tree<char, string> tree;
	tree.emplace('0', "123");

	EXPECT_TRUE(tree['0'] == "123");
	EXPECT_TRUE(tree.size() == 1);
}

TEST(Functions, At)
{
	avl_tree<char, string> tree;
	tree.insert(make_pair('0', "abc"));
	tree.insert(make_pair('1', "zxc"));
	tree.insert(make_pair('2', "klj"));

	EXPECT_TRUE(tree.at('0') == "abc");
}

TEST(Functions, Equal)
{
	avl_tree<char, string> tree1;
	tree1.insert(make_pair('0', "abc"));
	tree1.insert(make_pair('1', "zxc"));
	tree1.insert(make_pair('2', "klj"));

	avl_tree<char, string> tree2;
	tree2.insert(make_pair('0', "abc"));
	tree2.insert(make_pair('1', "zxc"));
	tree2.insert(make_pair('2', "klj"));

	EXPECT_TRUE(tree1 == tree2);

	tree2.emplace('r', "3123");
	EXPECT_FALSE(tree1 == tree2);
	tree1.emplace('z', "asdfa");
	EXPECT_FALSE(tree1 == tree2);
}

TEST(Functions, AssignOpertor)
{
	avl_tree<int, char> tree1;
	avl_tree<int, char> tree2({
		std::make_pair(0, '0'),
		std::make_pair(1, '1'),
		std::make_pair(100, '@')
	});

	tree1 = tree2;

	EXPECT_TRUE(tree1[0] == '0');
	EXPECT_TRUE(tree1[1] == '1');
	EXPECT_TRUE(tree1[100] == '@');
	EXPECT_TRUE(tree1.size() == 3);
}

TEST(Functions, MoveAssignOpertor)
{
	avl_tree<int, char> tree;

	tree = avl_tree<int, char>({
		make_pair(0, '0'),
		make_pair(1, '1'),
		make_pair(100, '@')
	});;

	EXPECT_TRUE(tree[0] == '0');
	EXPECT_TRUE(tree[1] == '1');
	EXPECT_TRUE(tree[100] == '@');
	EXPECT_TRUE(tree.size() == 3);
}

TEST(Global, Stress)
{
	avl_tree<int, int> tree;
	for (int i = 0; i < 1000000; ++i)
	{
		tree.insert({i, i * 3});
	}
	for (int i = 100; i < 999999; ++i)
	{
		tree.erase(i);
	}
	for (int i = 0; i < 1000000; ++i)
	{
		tree.insert({i, i * 3});
	}
	for (int i = 100; i < 999999; ++i)
	{
		tree.erase(i);
	}
	for (int i = 0; i < 1000000; ++i)
	{
		tree.insert({i, i * 3});
	}
	for (int i = 100; i < 999999; ++i)
	{
		tree.erase(i);
	}
	for (int i = 0; i < 100; ++i)
		EXPECT_TRUE(tree[i] == i * 3);
	EXPECT_TRUE(tree[999999] == 2999997);
	EXPECT_TRUE(tree.size() == 101);
	for (int i = 0; i < 1000; ++i)
		tree.insert({rand() % 1000000, rand()});
}

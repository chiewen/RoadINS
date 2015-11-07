#include <numeric>

#include "gtest/gtest.h"
#include "io/DataReader.h"

using namespace std;


int main(int argc, char* argv[]) {

    const string new_york_data = "D:\\work\\Data\\New York City\\USA-road-d.NY";
    const string usa_data = "D:\\work\\Data\\Full USA\\USA-road-d.USA";

    vector<shared_ptr<Node>> nodes = DataReader::read_data(new_york_data);

    cout << nodes.size() << endl;

    long roads = accumulate(nodes.begin(), nodes.end(), 0, [](long sum, const shared_ptr<Node>& node){
        return sum +  node->roads.size();
    }) / 2;

    cout << roads << endl;

    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

#include<iostream>
#include<vector>
#include<cstdlib>
#include<fstream>
//#include <json/json.h>
#include <sstream>
#include"item.cpp"
#include"knapsack.cpp"
#include"json.hpp"
#include"json_fwd.hpp"

using namespace std;

std::string formatPercentage(double percentage) {
    std::ostringstream oss;
    oss << std::fixed << std::setprecision(2) << percentage;
    return oss.str();
}

void testy(int liczba, int inputknapsackVolume, int inputknapsackMass, int opcja, int n, string inputfilename)
{

    Knapsack knapsack;
    vector<Item> items;
    vector<int> cos;
    float avggreddytime = 0, avgdynmamictime = 0, avgforcetime = 0, avgwheightedgreddytime = 0, solutionpercentagegreddy, solutionpercentagewgreddy;
    
    int zakres, optimalsolution = 0;
    float greedysolution = 0, wheightedgreedysolution = 0;
    switch (opcja)
    {
    case 1:
        {
        items.clear();    
        nlohmann::json n_const_random;
        std::ofstream n_const_random_file("output_const_n_random_elements.json");
        if (!n_const_random_file.is_open()) {
            std::cerr << "Unable to open json -file." << std::endl;
            return;
        }
            
        for(int i = 0; i < liczba; i++)
        {
            if(inputknapsackMass<inputknapsackVolume)
            {
                zakres = ((inputknapsackMass)/n)*3+1;
            }
            else
            {
                zakres = ((inputknapsackVolume)/n)*3+1;
            }
                for (int j = 0; j < n; j++)  
            {

                    items.push_back(Item(1+(rand()%zakres), 1+(rand()%zakres), 1+(rand()%zakres), j));
            }
            knapsack.setParameters(inputknapsackVolume, inputknapsackMass);

            avgforcetime += knapsack.force(items).count();
            optimalsolution += knapsack.getCurrentValue();
            knapsack.clear();
                

            avggreddytime += knapsack.greedy(items).count();
            greedysolution += knapsack.getCurrentValue();
            knapsack.clear();

            avgdynmamictime += knapsack.dynamicProgramming(items).count();
            knapsack.clear();

            avgwheightedgreddytime += knapsack.weightedGreedy(items).count();
            wheightedgreedysolution += knapsack.getCurrentValue();
            knapsack.clear();
            
            items.clear();
        }
        solutionpercentagewgreddy = (wheightedgreedysolution/optimalsolution)*100;
        solutionpercentagegreddy = (greedysolution/optimalsolution)*100;
        n_const_random["Average time and percentage of optimal solution."].push_back({
            {"n = " + std::to_string(n)},
            {"Greedy = " + std::to_string(avggreddytime / liczba) + "µs", formatPercentage(solutionpercentagegreddy) + "%"},
            {"Weighted Greedy = " + std::to_string(avgwheightedgreddytime / liczba) + "µs", formatPercentage(solutionpercentagewgreddy) + "%"},
            {"Dynamic = " + std::to_string(avgdynmamictime / liczba) + "µs", "100.00%"},
            {"Force = " + std::to_string(avgforcetime / liczba) + "µs", "100.00%"}
        });
        
        avggreddytime = 0;
        avgforcetime = 0;
        avgdynmamictime = 0;
        avgwheightedgreddytime = 0;
        wheightedgreedysolution = 0;
        greedysolution = 0;
        optimalsolution = 0;
        
    
    
    /*for (const auto& item : items) {
        nlohmann::json itemJson;
        item.to_json(itemJson);
        jsonData["items"].push_back(itemJson);
    }*/
    
        n_const_random_file << n_const_random.dump(4);
        n_const_random_file.close();
        break;
    }
        
    
    case 2:
        {
        items.clear();
        nlohmann::json jsonData;
        std::ofstream outputFile("output_variable_n_random_elements.json");
        if (!outputFile.is_open()) {
            std::cerr << "Unable to open json -file." << std::endl;
            return;
        }
        for(int size = 2; size <= n; size+=1)
        {
            
            for(int i = 0; i < liczba; i++)
            {
                if(inputknapsackMass<inputknapsackVolume)
                {
                    zakres = ((inputknapsackMass)/size)*3+1;
                }
                else
                {
                    zakres = ((inputknapsackVolume)/size)*3+1;
                }
                for (int j = 0; j < size; j++)  
                {

                    items.push_back(Item(1+(rand()%zakres), 1+(rand()%zakres), 1+(rand()%zakres), j));
                }
                knapsack.setParameters(inputknapsackVolume, inputknapsackMass);
                //cout<<items.size()<<endl;
                avgforcetime += knapsack.force(items).count();
                optimalsolution += knapsack.getCurrentValue();
                knapsack.clear();
                

                avggreddytime += knapsack.greedy(items).count();
                greedysolution += knapsack.getCurrentValue();
                knapsack.clear();

                avgdynmamictime += knapsack.dynamicProgramming(items).count();
                knapsack.clear();

                avgwheightedgreddytime += knapsack.weightedGreedy(items).count();
                wheightedgreedysolution += knapsack.getCurrentValue();
                knapsack.clear();
                
                items.clear();
            }
            solutionpercentagewgreddy = (wheightedgreedysolution/optimalsolution)*100;
            solutionpercentagegreddy = (greedysolution/optimalsolution)*100;
            jsonData["Average time and percentage of optimal solution for different amounts of items"].push_back({
                {"n = " + std::to_string(size)},
                {"Greedy = " + std::to_string(avggreddytime / liczba) + "µs", formatPercentage(solutionpercentagegreddy) + "%"},
                {"Weighted Greedy = " + std::to_string(avgwheightedgreddytime / liczba) + "µs", formatPercentage(solutionpercentagewgreddy) + "%"},
                {"Dynamic = " + std::to_string(avgdynmamictime / liczba) + "µs", "100.00%"},
                {"Force = " + std::to_string(avgforcetime / liczba) + "µs", "100.00%"}
            });
            //cout<<avggreddytime/liczba<<endl;
            avggreddytime = 0;
            avgforcetime = 0;
            avgdynmamictime = 0;
            avgwheightedgreddytime = 0;
            wheightedgreedysolution = 0;
            greedysolution = 0;
            optimalsolution = 0;
            //cout<<size<<endl;
        }
        
        /*for (const auto& item : items) {
            nlohmann::json itemJson;
            item.to_json(itemJson);
            jsonData["items"].push_back(itemJson);
        }*/
        
        outputFile << jsonData.dump(4);
        outputFile.close();
        break;

    }
    case 3:
        {
        items.clear();
        nlohmann::json n_const_random_ff;
        ofstream n_const_random_file_ff("output_const_n_elements_from_file.json");
        if (!n_const_random_file_ff.is_open()) {
            std::cerr << "Unable to open json -file." << std::endl;
            return;
        }
        nlohmann::json input;
        ifstream inputfile(inputfilename);
        if (!inputfile.is_open()) {
            std::cerr << "Unable to open json -file." << std::endl;
            return;
        }
        inputfile>>input;
        inputfile.close();
        n = input["n"] ;
        //cout<<n; 
        
        for (const auto& itemData : input["Items"]) {
            int index = 0, value = 0;
            double volume = 0.0, mass = 0.0;

            // Parse each attribute from the array of strings
            for (const auto& attribute : itemData) {
                // Convert the attribute to a string before using std::istringstream
                std::string attributeStr = attribute;
                std::istringstream iss(attributeStr);
                std::string key, equalSign;
                
                // Extract key, equal sign, and value from each string
                iss >> key >> equalSign >> value;

                if (key == "index") {
                    index = value;
                } else if (key == "volume") {
                    volume = value;
                } else if (key == "mass") {
                    mass = value;
                } else if (key == "value") {
                    value = value;
                }
            }

        // Push back a new Item into the vector
        items.push_back(Item(value, volume, mass, index));
    }
            knapsack.setParameters(inputknapsackVolume, inputknapsackMass);
        for(int i = 0; i < liczba; i++ )
        {
            avgforcetime += knapsack.force(items).count();
            optimalsolution += knapsack.getCurrentValue();
            knapsack.clear();
                

            avggreddytime += knapsack.greedy(items).count();
            greedysolution += knapsack.getCurrentValue();
            knapsack.clear();

            avgdynmamictime += knapsack.dynamicProgramming(items).count();
            knapsack.clear();

            avgwheightedgreddytime += knapsack.weightedGreedy(items).count();
            wheightedgreedysolution += knapsack.getCurrentValue();
            knapsack.clear();
        }
            items.clear();
        
        solutionpercentagewgreddy = (wheightedgreedysolution/optimalsolution)*100;
        solutionpercentagegreddy = (greedysolution/optimalsolution)*100;
        n_const_random_ff["Average time and percentage of optimal solution."].push_back({
            {"n = " + std::to_string(n)},
            {"Greedy = " + std::to_string(avggreddytime / liczba) + "µs", formatPercentage(solutionpercentagegreddy) + "%"},
            {"Weighted Greedy = " + std::to_string(avgwheightedgreddytime / liczba) + "µs", formatPercentage(solutionpercentagewgreddy) + "%"},
            {"Dynamic = " + std::to_string(avgdynmamictime / liczba) + "µs", "100.00%"},
            {"Force = " + std::to_string(avgforcetime / liczba) + "µs", "100.00%"}
        });
        
        avggreddytime = 0;
        avgforcetime = 0;
        avgdynmamictime = 0;
        avgwheightedgreddytime = 0;
        wheightedgreedysolution = 0;
        greedysolution = 0;
        optimalsolution = 0;
        
    
    
   
    
        n_const_random_file_ff << n_const_random_ff.dump(4);
        n_const_random_file_ff.close();
        break;
    }
    case 4:
        {
        vector<Item> items2;
        std::vector<int> numbers;
        items.clear();
        nlohmann::json n_variable_random_ff;
        ofstream n_variable_random_file_ff("output_variable_n_elements_from_file.json");
        if (!n_variable_random_file_ff.is_open()) {
            std::cerr << "Unable to open json -file." << std::endl;
            return;
        }
        nlohmann::json input_variable;
        ifstream inputfile_variable(inputfilename);
        if (!inputfile_variable.is_open()) {
            std::cerr << "Unable to open json -file." << std::endl;
            return;
        }
        inputfile_variable>>input_variable;
        inputfile_variable.close();
        n = input_variable["n"] ;
        //cout<<n; 
        int j = 0;
        
        knapsack.setParameters(inputknapsackVolume, inputknapsackMass);

        for(int size = 2; size <= n; size+=1)
        {
                
            for(int i = 0; i < liczba; i++)
            {
                //items2.clear();
                //numbers.clear();
                /*for (int i = 0; i < size; i++) {
                    int randomNumber;
                    do {
                        // Generate a random number in the range from 0 to n-1
                        randomNumber = std::rand() % n + 1;
                    }
                    while (std::find(numbers.begin(), numbers.end(), randomNumber) != numbers.end());
                    
                    // Add the unique random number to the vector
                    numbers.push_back(randomNumber);
                }
                for (int i : numbers)
                {
                    items2.push_back(items[i]);
                }*/
                for (const auto& itemData : input_variable["Items"]) {
                    int index = 0, value = 0;
                    double volume = 0.0, mass = 0.0;

                    // Parse each attribute from the array of strings
                    for (const auto& attribute : itemData) {
                        // Convert the attribute to a string before using std::istringstream
                        std::string attributeStr = attribute;
                        std::istringstream iss(attributeStr);
                        std::string key, equalSign;
                        
                        // Extract key, equal sign, and value from each string
                        iss >> key >> equalSign >> value;

                        if (key == "index") {
                            index = value;
                        } else if (key == "volume") {
                            volume = value;
                        } else if (key == "mass") {
                            mass = value;
                        } else if (key == "value") {
                            value = value;
                        }
                    }

            // Push back a new Item into the vector
            if(items.size()<=size)
                {items.push_back(Item(value, volume, mass, index));}
            }
                knapsack.setParameters(inputknapsackVolume, inputknapsackMass);
                //cout<<items2.size()<<endl;
                avgforcetime += knapsack.force(items).count();
                optimalsolution += knapsack.getCurrentValue();
                knapsack.clear();
                

                avggreddytime += knapsack.greedy(items).count();
                greedysolution += knapsack.getCurrentValue();
                knapsack.clear();

                avgdynmamictime += knapsack.dynamicProgramming(items).count();
                knapsack.clear();

                avgwheightedgreddytime += knapsack.weightedGreedy(items).count();
                wheightedgreedysolution += knapsack.getCurrentValue();
                knapsack.clear();
                
                items.clear();
            }
            solutionpercentagewgreddy = (wheightedgreedysolution/optimalsolution)*100;
            solutionpercentagegreddy = (greedysolution/optimalsolution)*100;
            n_variable_random_ff["Average time and percentage of optimal solution for different amounts of items"].push_back({
                {"n = " + std::to_string(size)},
                {"Greedy = " + std::to_string(avggreddytime / liczba) + "µs", formatPercentage(solutionpercentagegreddy) + "%"},
                {"Weighted Greedy = " + std::to_string(avgwheightedgreddytime / liczba) + "µs", formatPercentage(solutionpercentagewgreddy) + "%"},
                {"Dynamic = " + std::to_string(avgdynmamictime / liczba) + "µs", "100.00%"},
                {"Force = " + std::to_string(avgforcetime / liczba) + "µs", "100.00%"}
            });
            //cout<<avggreddytime/liczba<<endl;
            avggreddytime = 0;
            avgforcetime = 0;
            avgdynmamictime = 0;
            avgwheightedgreddytime = 0;
            wheightedgreedysolution = 0;
            greedysolution = 0;
            optimalsolution = 0;
        }
        n_variable_random_file_ff << n_variable_random_ff.dump(4);
        n_variable_random_file_ff.close();
        break;
    }

    default:
        break;
    }    
}
int main()
{

    srand((unsigned) time(NULL));
    int size = 20, j=0, inputknapsackMass, inputknapsackVolume,value,value1, zakres, liczba;
    vector<Item> items, knapsackitems, knapsackitems1, knapsackitems2, knapsackitems3;
    const char* pythonScript;
    int amountoftests, n;
    string command;
    int returnValue, input2, opcja;
    
    nlohmann::json input;
    ifstream inputfile("input.json");
    if (!inputfile.is_open()) {
        std::cerr << "Unable to open json -file." << std::endl;
        return 0;
    }
    inputfile>>input;
    inputfile.close();
    if(input["Knapsack Volume"] == 0)
    {
        inputknapsackVolume = (rand()%100)+50;
    }
    else{inputknapsackVolume = input["Knapsack Volume"];}
    if(input["Knapsack Mass"] == 0)
    {
        inputknapsackMass = (rand()%100)+50;
    }
    else{inputknapsackMass = input["Knapsack Mass"];}
    if(input["Random elements"] == "Yes" && input["Changing n"] == "No")
    {opcja = 1;}
    else if(input["Random elements"] == "Yes" && input["Changing n"] == "Yes")
    {opcja = 2;}
    else if(input["Random elements"] == "No" && input["Changing n"] == "No")
    {opcja = 3;}
    else if(input["Random elements"] == "No" && input["Changing n"] == "Yes")
    {opcja = 4;}
    amountoftests = input["Amount of tests"];
    n = input["n"];
    testy(amountoftests, inputknapsackVolume, inputknapsackMass, opcja, n, "input.json");

    pythonScript = "wykresy.py";
    command = "python " + string(pythonScript);    
    returnValue = system(command.c_str());


    
    
    return 0;
}
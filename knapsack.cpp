#pragma once
#include "item.cpp"
#include <vector>
#include <algorithm>
#include <cmath>
#include <bitset>
#include <chrono>
#include <fstream>
bool CompareByMassRatio(const Item& a, const Item& b) {
    // Calculate the ratio value / mass for both objects a and b
    double ratio_a = a.getValue() / a.getMass();
    double ratio_b = b.getValue() / b.getMass();

    return ratio_a > ratio_b;
}
bool CompareByVolumeRatio(const Item& a, const Item& b) {
    // Calculate the ratio value / mass for both objects a and b
    double ratio_a = a.getValue() / a.getVolume();
    double ratio_b = b.getValue() / b.getVolume();

    return ratio_a > ratio_b;
}
class Knapsack
{
    private:
        int volumeCapacity;
        int massCapacity;
        int currentVolume;
        int currentMass;
        float currentValue;
        vector<Item> items;
        ofstream a,b,c,d;
    public:
        Knapsack(){currentMass = 0; currentVolume = 0; currentValue = 0;}
        void setParameters(int volume, int mass)
        {
            volumeCapacity = volume;
            massCapacity = mass;
        }
        bool putItem(Item item)
        {
            if ((currentMass + item.getMass()) <= massCapacity && (currentVolume + item.getVolume()) <= volumeCapacity)
            {
                items.push_back(item);
                currentMass+=item.getMass();
                currentVolume+=item.getVolume();
                currentValue+=item.getValue();
                return true;
            }
            else {return false;}
        }
      
        void clear()
        {
            items.clear();
            currentVolume = 0;
            currentMass = 0;
            currentValue = 0;
        }
        /*void removeItem(int id)
        {
            items.erase(remove_if(items.begin(), items.end(), [id](const Item& i) { return i.getId() == id; }), items.end());
        }*/
        int getVolumeCapacity()
        {
            return volumeCapacity;
        }
        int getMassCapacity()
        {
            return massCapacity;
        }
        int getCurrentMass()
        {
            return currentMass;
        }
        int getCurrentVolume()
        {
            return currentVolume;
        }
        int getCurrentValue()
        {
            return currentValue;
        }
        vector<Item> getItems()
        {
            return items;
        }
        auto greedy(vector<Item> input)
        {
            srand((unsigned) time(NULL));
            auto start = std::chrono::high_resolution_clock::now();
            int i = 0, value = 0;
            if(massCapacity < volumeCapacity)
                {sort(input.begin(), input.end()-1, CompareByMassRatio);}
            else
                {sort(input.begin(), input.end()-1, CompareByVolumeRatio);}
            while (i < input.size())
            {
                putItem(input[i]);
                i++;
            }
            auto stop = std::chrono::high_resolution_clock::now();
            auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
            return duration;

        }
        auto weightedGreedy(vector<Item> input)
        {
            srand((unsigned) time(NULL));
            auto start = std::chrono::high_resolution_clock::now();
            int i = 0, value = 0;
            double mass = massCapacity, volume = volumeCapacity;
            sort(input.begin(), input.end()-1, [mass, volume](const Item& a, const Item& b)
            {
                double ratio = mass / (mass + volume);
                double ratio2 = volume / (mass + volume);
                double ratio_a = a.getValue() / ((a.getVolume() * (ratio2)) + (a.getMass() * ratio));
                double ratio_b = b.getValue() / ((b.getVolume() * (ratio2)) + (b.getMass() * ratio));

                return ratio_a > ratio_b;   
            });
            while (i < input.size())
            {
                putItem(input[i]); 
                i++;
            }
            auto stop = std::chrono::high_resolution_clock::now();
            auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
            return duration;
        }
        auto force(vector<Item> input)
        {
            srand((unsigned) time(NULL));
            auto start = std::chrono::high_resolution_clock::now();
            int maxvalue = 0;
            vector<Item> maxKnapsack;
            for(int i = 0; i < pow(2,input.size()); i++)
            {
                string binary = bitset<32>(i).to_string();
                for(int j = binary.size() - 1; j >= binary.size()-input.size(); j--)
                {
                    if(binary[j]=='1')
                    {
                        putItem(input[31-j]);
                        
                    }   
                }
                if (currentValue>maxvalue)
                {
                    maxvalue = currentValue;
                    maxKnapsack = items;
                    //cout<<maxvalue<<endl;
                }
                clear();
            }
            for(int i = 0; i < maxKnapsack.size(); i++)
            {
                putItem(maxKnapsack[i]);
            }
            auto stop = std::chrono::high_resolution_clock::now();
            auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
            return duration;
        }
        auto dynamicProgramming(std::vector<Item>& input)
        {

        srand((unsigned) time(NULL));
        auto start = std::chrono::high_resolution_clock::now();
        int n = input.size();
        std::vector<std::vector<std::vector<int>>> dp(n + 1, std::vector<std::vector<int>>(massCapacity + 1, std::vector<int>(volumeCapacity + 1, 0)));

        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= massCapacity; j++) {
                for (int k = 1; k <= volumeCapacity; k++) {
                    if (input[i - 1].getMass() <= j && input[i - 1].getVolume() <= k) {
                        dp[i][j][k] = std::max(dp[i - 1][j][k], dp[i - 1][j - input[i - 1].getMass()][k - input[i - 1].getVolume()] + input[i - 1].getValue());
                    } else {
                        dp[i][j][k] = dp[i - 1][j][k];
                    }
                }
            }
        }

        int i = n, j = massCapacity, k = volumeCapacity;
        while (i > 0 && j >= 0 && k >= 0) {
            if (dp[i][j][k] != dp[i - 1][j][k]) {
                putItem(input[i - 1]);
                j -= input[i - 1].getMass();
                k -= input[i - 1].getVolume();
            }
        i--;
    }
    currentValue = dp[n][massCapacity][volumeCapacity];
    auto stop = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
    return duration;

}
        void displayItems()
        {
            for (int i = 0; i <= items.size() - 1; i++)
            {
                cout<<"Item id: "<<items[i].getId()<<" Mass: "<<items[i].getMass()<<" Volume: "<<items[i].getVolume()<<" Value: "<<items[i].getValue()<<endl;
            }
        }
};

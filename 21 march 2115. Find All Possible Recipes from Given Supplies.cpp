#include <vector>
#include <string>
#include <unordered_map>
#include <queue>

using namespace std;

class Solution {
public:
    vector<string> findAllRecipes(vector<string>& recipes, vector<vector<string>>& ingredients, vector<string>& supplies) {
        // Create a graph to represent the dependencies.
        unordered_map<string, vector<string>> dependencyGraph;
        // This will keep track of the in-degrees of each recipe.
        unordered_map<string, int> inDegrees;
      
        // Build the graph and initialize the in-degrees.
        for (int i = 0; i < recipes.size(); ++i) {
            for (const auto& ingredient : ingredients[i]) {
                dependencyGraph[ingredient].push_back(recipes[i]);
            }
            inDegrees[recipes[i]] = ingredients[i].size();
        }

        // Initialize a queue with the initial supplies available.
        queue<string> q;
        for (const auto& supply : supplies) {
            q.push(supply);
        }

        // This will hold the recipes that can be cooked.
        vector<string> achievableRecipes;

        // Process each supply to see if recipes can be made.
        while (!q.empty()) {
            int queueSize = q.size();
            while (queueSize--) {
                string ingredient = q.front(); // The current ingredient to process.
                q.pop();

                // Traverse the adjacency list of the current ingredient.
                for (const auto& recipe : dependencyGraph[ingredient]) {
                    // As we are able to cook with this ingredient, decrement the in-degree.
                    // An in-degree of 0 implies all ingredients for this recipe are available.
                    if (--inDegrees[recipe] == 0) {
                        achievableRecipes.push_back(recipe); // Add the recipe to the answer list.
                        q.push(recipe); // Add the recipe to the queue as a new potential ingredient.
                    }
                }
            }
        }
      
        // Return the list of recipes that can be cooked.
        return achievableRecipes;
    }
};
#include <algorithm>
#include <iostream>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <utility>
#include <vector>

// Demo of Enhancements
// - hash indexing (unordered_multimap)
// - sorted vector + binary search (lower_bound/upper_bound)

struct Animal {
    int id;
    std::string animal_type;
    std::string breed;
    int age_weeks;
};

struct AgeIndexRow {
    int age_weeks;
    int id;
};

class AnimalCache {
public:
    explicit AnimalCache(std::vector<Animal> animals)
        : animals_(std::move(animals)) {
        rebuild_cache();
    }

    void rebuild_cache() {
        eq_index_.clear();
        age_sorted_.clear();

        // Build equality index
        for (const auto& a : animals_) {
            eq_index_["animal_type"].emplace(a.animal_type, a.id);
            eq_index_["breed"].emplace(a.breed, a.id);
            age_sorted_.push_back({a.age_weeks, a.id});
        }

        // Sort for binary-search range queries
        std::sort(age_sorted_.begin(), age_sorted_.end(),
                  [](const AgeIndexRow& x, const AgeIndexRow& y) {
                      return x.age_weeks < y.age_weeks;
                  });
    }

    // Hash index equality lookup
    std::vector<int> find_eq(const std::string& field, const std::string& value, int limit = 10) const {
        std::vector<int> ids;
        auto it = eq_index_.find(field);
        if (it == eq_index_.end()) return ids;

        auto range = it->second.equal_range(value);
        for (auto p = range.first; p != range.second && (int)ids.size() < limit; ++p) {
            ids.push_back(p->second);
        }
        return ids;
    }

    // Binary-search range query on sorted vector
    std::vector<int> find_age_range(int min_weeks, int max_weeks, int limit = 10) const {
        if (min_weeks > max_weeks) std::swap(min_weeks, max_weeks);

        auto lb = std::lower_bound(
            age_sorted_.begin(), age_sorted_.end(), min_weeks,
            [](const AgeIndexRow& row, int v) { return row.age_weeks < v; }
        );

        auto ub = std::upper_bound(
            age_sorted_.begin(), age_sorted_.end(), max_weeks,
            [](int v, const AgeIndexRow& row) { return v < row.age_weeks; }
        );

        std::vector<int> ids;
        for (auto it = lb; it != ub && (int)ids.size() < limit; ++it) {
            ids.push_back(it->id);
        }
        return ids;
    }

    const Animal* get_by_id(int id) const {
        for (const auto& a : animals_) {
            if (a.id == id) return &a;
        }
        return nullptr;
    }

private:
    std::vector<Animal> animals_;

    // field -> multimap(value -> id)
    using MultiMap = std::unordered_multimap<std::string, int>;
    std::unordered_map<std::string, MultiMap> eq_index_;

    std::vector<AgeIndexRow> age_sorted_;
};

int main() {
    std::vector<Animal> animals = {
        {1, "Dog", "Labrador", 12},
        {2, "Cat", "Siamese", 20},
        {3, "Dog", "Beagle", 8},
        {4, "Dog", "Labrador", 30},
        {5, "Cat", "Tabby", 15},
        {6, "Dog", "Husky", 25},
        {7, "Dog", "Beagle", 18},
    };

    AnimalCache cache(animals);

    std::cout << "=== Hash Index Equality Lookup (animal_type = Dog) ===\n";
    auto dog_ids = cache.find_eq("animal_type", "Dog", 5);
    std::cout << "Found " << dog_ids.size() << " matching IDs:\n";
    for (int id : dog_ids) {
        const auto* a = cache.get_by_id(id);
        std::cout << "  id=" << id << " type=" << a->animal_type
                  << " breed=" << a->breed << " age_weeks=" << a->age_weeks << "\n";
    }

    std::cout << "\n=== Binary Search Age Range (10..20 weeks) ===\n";
    auto range_ids = cache.find_age_range(10, 20, 10);
    std::cout << "Found " << range_ids.size() << " matching IDs:\n";
    for (int id : range_ids) {
        const auto* a = cache.get_by_id(id);
        std::cout << "  id=" << id << " type=" << a->animal_type
                  << " breed=" << a->breed << " age_weeks=" << a->age_weeks << "\n";
    }

    return 0;
}
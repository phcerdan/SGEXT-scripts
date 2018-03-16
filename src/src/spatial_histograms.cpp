#include "spatial_histograms.hpp"
#include <algorithm>
#include <cmath>

namespace SG {
void print_histogram(const histo::Histo<double> & histo, std::ostream & os)
{
    os << "# " << histo.name << ": L0:centers of bins, L1:counts, L2:breaks" << std::endl;
    histo.PrintCenters(os);
    histo.PrintCounts(os);
    histo.PrintBreaks(os);
}

histo::Histo<double> read_histogram(std::istream & is, const std::string & name)
{
    histo::Histo<double> histo;
    histo.name = name;
    std::string line;
    std::istringstream ss;
    double num;
    // Header, ignore
    std::getline(is, line);
    // Centers, ignore
    std::getline(is, line);
    // Counts, store
    std::getline(is, line);
    ss.str(line);
    while(ss >> num)
    {
        histo.counts.push_back(num);
    }
    // Breaks, store
    std::getline(is, line);
    ss.str(line);
    ss.clear();
    while(ss >> num)
    {
        histo.breaks.push_back(num);
    }

    // Complete histogram:
    histo.bins = histo.counts.size();
    histo.range.first = histo.breaks[0];
    histo.range.second = histo.breaks.back();
    return histo;
}

histo::Histo<double> histogram_degrees(
        const std::vector<unsigned int> & degrees,
        size_t bins)
{
	auto max_degree = *std::max_element(std::begin(degrees), std::end(degrees) );
    // Generate breaks to get middle of the bins to be the integer
    // value of the degree
    histo::Histo<double> hist_degrees;
    if(bins == 0)
        hist_degrees = histo::Histo<double>(degrees,
                histo::GenerateBreaksFromRangeAndBins(
                    -0.5, max_degree + 0.5, max_degree + 1)
                );
    else
        hist_degrees = histo::Histo<double>(degrees,
                histo::GenerateBreaksFromRangeAndBins(
                    -0.5, max_degree + 0.5, bins)
                );
    hist_degrees.name = "degrees";
    return hist_degrees;
}

histo::Histo<double> histogram_distances(const std::vector<double> & distances, size_t bins )
{
	auto max_distance = *std::max_element(std::begin(distances), std::end(distances) );
    histo::Histo<double> hist_distances;
    if(bins == 0)
        hist_distances = histo::Histo<double>(distances);
    else
        hist_distances = histo::Histo<double>(distances,
                histo::GenerateBreaksFromRangeAndBins(
                    0.0, max_distance + 100 * std::numeric_limits<double>::epsilon(), bins)
                );
    hist_distances.name = "distances";
    return hist_distances;
}

histo::Histo<double> histogram_angles(const std::vector<double> & angles, size_t bins )
{
    constexpr auto pi = 3.14159265358979323846;
    histo::Histo<double> hist_angles;
    if(bins == 0)
        hist_angles = histo::Histo<double>(angles, std::make_pair(0.0, pi));
    else
        hist_angles = histo::Histo<double>(angles,
                histo::GenerateBreaksFromRangeAndBins(
                    0.0, pi, bins)
                );
    hist_angles.name = "angles";
    return hist_angles;
}

histo::Histo<double> histogram_cosines(const std::vector<double> & cosines, size_t bins )
{
    histo::Histo<double> hist_cosines;
    if(bins == 0)
        hist_cosines = histo::Histo<double>(cosines, std::make_pair(-1.0, 1.0));
    else
        hist_cosines = histo::Histo<double>(cosines,
                histo::GenerateBreaksFromRangeAndBins(
                    -1.0, 1.0, bins)
                );
    hist_cosines.name = "cosines";
    return hist_cosines;
}
} //end namespace
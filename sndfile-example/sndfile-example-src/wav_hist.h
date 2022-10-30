#ifndef WAVHIST_H
#define WAVHIST_H

#include <fstream>
#include <iostream>
#include <vector>
#include <map>
#include <sndfile.hh>

class WAVHist {
  private:
	std::vector<std::map<short, size_t>> counts;
	std::map<short, size_t> MID_channel;
	std::map<short, size_t> SIDE_channel;


  public:
	WAVHist(const SndfileHandle& sfh) {
		counts.resize(sfh.channels());
	}

	void update(const std::vector<short>& samples) {
		size_t n { };
		short aux { 0 };
		for(auto s : samples){
		 	if(n%2 == 0){
				aux = s;
			}else{	
				std::cout << aux << " " << s << " s->" <<(aux-s)/2 << " m-> "<< (aux+s)/2 << std::endl;
				MID_channel[short((aux+s)/2)]++;
				SIDE_channel[short((aux-s)/2)]++;
			}
			counts[n++ % counts.size()][aux]++;
		}
		std::ofstream out_file2("SIDE_channel.txt");
		std::ofstream out_file("MID_channel.txt");
		for(auto [value, counter] : SIDE_channel)
			out_file2 << value << '\t' << counter << '\n';
		for(auto [value, counter] : MID_channel)
			out_file << value << '\t' << counter << '\n';
		out_file.close();

	}

	void dump(const size_t channel) const {
		for(auto [value, counter] : counts[channel])
			std::cout << value << '\t' << counter << '\n';
	}

};

#endif 
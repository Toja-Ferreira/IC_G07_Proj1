#include <iostream>
#include <sndfile.hh>
#include <vector>
#include <cmath>
using namespace std;

constexpr size_t FRAMES_BUFFER_SIZE = 65536; // Buffer for reading/writing frames

int main(int argc, char *argv[]) {
    SndfileHandle sOG { argv[argc-2] };
    SndfileHandle sCO { argv[argc-1] };
    if(argc < 3) {
		cerr << "Usage: wav_cp <orignal filename> <compressed filename>" << endl;
		return 1;
	}
	if((sOG.format() & SF_FORMAT_SUBMASK) != SF_FORMAT_PCM_16 || (sCO.format() & SF_FORMAT_SUBMASK) != SF_FORMAT_PCM_16) {
		cerr << "Error: file is not in PCM_16 format\n";
		return 1;
	}
	if((sOG.format() & SF_FORMAT_TYPEMASK) != SF_FORMAT_WAV || (sCO.format() & SF_FORMAT_TYPEMASK) != SF_FORMAT_WAV) {
		cerr << "Error: file is not in WAV format\n";
		return 1;
	}

	if(sOG.error() || sCO.error()) {
		cerr << "Error: invalid input file\n";
		return 1;
    }

    if((sOG.samplerate() * sOG.channels()) != (sCO.samplerate() * sCO.channels())){
        cerr << "files do not have the same number of samples" << endl;
        return 1;
    }
    double d = 0, s=0;
    double Maxerr = 0, tmp;
    double n = sOG.frames()*sOG.channels();

    size_t nOG;
    vector<short> OG(FRAMES_BUFFER_SIZE * sOG.channels());

    size_t nCO;
    vector<short> CO(FRAMES_BUFFER_SIZE * sCO.channels());

    while((nOG = sOG.readf(OG.data(), FRAMES_BUFFER_SIZE)), (nCO = sCO.readf(CO.data(), FRAMES_BUFFER_SIZE))){
        OG.resize(nOG * sOG.channels());
        CO.resize(nOG * sCO.channels());
        //iterate samples
        for(int i = 0; i< OG.size(); ++i){
            d+= pow(OG[i]-CO[i], 2);
            s += pow(OG[i], 2);
            tmp = abs(OG[i] - CO[i]);
            if(tmp > Maxerr)
                Maxerr = tmp;
        }
    }

    d = (1/n) * d;
    s = (1/n) * s;
    double SNR = 10*log10(s/d);
    cout << "\033[1;34mSNR: " << SNR << " dB\nMaximum per sample absolute error: " << Maxerr << "\033[0m" << endl;
}
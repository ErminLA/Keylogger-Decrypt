#include <fstream>
#include <iostream>
#include <string>
#include <vector>

std::string DecryptB64 (std::string s);
std::string base64_decode(const std::string &s);

const std::string &SALT1 = "LM::TB::BB";
const std::string &SALT2 = "__:/__77";
const std::string &SALT3 = "line=wowC++";

int main(int argc, char *argv[]) {

	std::string test;
	std::ifstream iFile(argv[1]);
	iFile >> test;
	std::cout << "DECRYPTED: " << DecryptB64(test);

	return 0;
}

const std::string &BASE64_CODES = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";

std::string DecryptB64 (std::string s) {
        s = s.erase (7, 1);
        s = s.erase (1, 1);
        s = base64_decode (s);
        s = s.substr (SALT2.length() + SALT3.length());
        s = s.substr (0, s.length() - SALT1.length());
        s = base64_decode (s);
        s = s.substr (0, s.length() - SALT1.length());
        s = s.erase (7, SALT3.length());
        s = base64_decode (s);
        s = s.substr (SALT1.length());
        s = s.substr (0, s.length() - SALT2.length() - SALT3.length());
        return s;
   }

std::string base64_decode(const std::string &s) {
        std::string ret;
        std::vector<int> vec(256, -1);
        for (int i = 0; i < 64; i++)
            vec [BASE64_CODES[i]] = i;
        int val = 0, bits = -8;
        for (const auto &c : s)
            {
                if (vec[c] == -1) break;
                val = (val << 6) + vec[c];
                bits += 6;

                if (bits >= 0)
                    {

                        ret.push_back(char((val >> bits) & 0xFF));
                        bits -= 8;
                    }
            }

        return ret;
}

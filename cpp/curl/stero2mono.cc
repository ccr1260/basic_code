#include <fstream>
#include <cstring>

void mix_down_stereo_to_mono(void *input, void *output, size_t size) {
    for (size_t i = 0; i < (size / 4); i++) { // 因为是16位双声道，所以跳过每个声道的2个字节

        // 每四个字节只写两个字节
        memcpy(output + (2 * i), input + (4 * i), 2);
        // 提取左声道和右声道的样本
        // short left = *reinterpret_cast<const short*>(input + i);
        // short right = *reinterpret_cast<const short*>(input + i + 2);

        // // 将左声道和右声道的样本以1:1的比例混合为单声道
        // short mixed = (left + right) >> 1; // 算术右移以丢弃高位

        // // 将混合后的单声道样本放入输出缓冲区
        // *reinterpret_cast<short*>(output + i) = mixed;
    }
}

void downSample(int inRate, int outRate, short* inData, short* outData, int inDataLength, bool stereo2mono)
{
    int factor = inRate / outRate;
    if (stereo2mono)
        factor = factor * 2;
    for (int i = 0; i < (inDataLength / factor); i++) {
        memcpy(outData + i, inData + (factor * i), 2);
    }
}

int main()
{
    std::ifstream inputFile("input_20240411183337.wav", std::ios::binary);
    std::ofstream outputFile("mono.wav", std::ios::binary);

    int sampleSize = 2;
    char buffer[sampleSize];

    while (inputFile.read(buffer, sampleSize * 4))
    {
        outputFile.write(buffer, sampleSize);
    }
}
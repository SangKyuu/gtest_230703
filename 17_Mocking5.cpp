// 17_Mocking5.cpp
#include <iostream>

struct Packet { };

class PacketStream {
public:
    void AppendPacket(Packet* newPacket)
    {
        std::cout << "Append Packet" << std::endl;
    }

    const Packet* GetPacket(size_t packetNumber) const
    {
        std::cout << "GetPacket: " << packetNumber << std::endl;
        return nullptr;
    }
};

class PacketReader {
public:
    // IPacketStream 타입은 반드시
    //  AppendPacket / GetPacket 함수를 제공해야 합니다.
    // => 암묵적인 인터페이스의 약속

    template <typename IPacketStream>
    void ReadPacket(IPacketStream* stream, size_t packetNumber)
    {
        // ...
        stream->AppendPacket(nullptr);
        stream->GetPacket(packetNumber);
    }
};
//-------
#include <gmock/gmock.h>

// 암묵적인 인터페이스를 사용하는 경우의 Mocking
class MockPacketStream {
public:
    MOCK_METHOD(void, AppendPacket, (Packet * newPacket));
    MOCK_METHOD(const Packet*, GetPacket, (size_t packetNumber), (const));
};

TEST(PacketReaderTest, Sample)
{
    // PacketStream stream;
    MockPacketStream stream;
    PacketReader reader;

    EXPECT_CALL(stream, AppendPacket(nullptr));
    EXPECT_CALL(stream, GetPacket(42));

    reader.ReadPacket(&stream, 42);
}

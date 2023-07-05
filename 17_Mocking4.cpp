// 17_Mocking4.cpp
#include <iostream>

struct Packet { };

class IPacketStream {
public:
    virtual ~IPacketStream() { }

    virtual void AppendPacket(Packet* newPacket) = 0;
    virtual const Packet* GetPacket(size_t packetNumber) const = 0;
};

class PacketStream : public IPacketStream {
public:
    void AppendPacket(Packet* newPacket) override
    {
        std::cout << "Append Packet" << std::endl;
    }

    const Packet* GetPacket(size_t packetNumber) const override
    {
        std::cout << "GetPacket: " << packetNumber << std::endl;
        return nullptr;
    }
};

class PacketReader {
public:
    void ReadPacket(IPacketStream* stream, size_t packetNumber)
    {
        // ...
        stream->AppendPacket(nullptr);
        stream->GetPacket(packetNumber);
    }
};
//-------
#include <gmock/gmock.h>

class MockPacketStream : public IPacketStream {
public:
    MOCK_METHOD(void, AppendPacket, (Packet * newPacket), (override));
    MOCK_METHOD(const Packet*, GetPacket, (size_t packetNumber), (const, override));
};

TEST(PacketReaderTest, Sample)
{
    MockPacketStream stream;
    PacketReader reader;

    EXPECT_CALL(stream, AppendPacket(nullptr));
    EXPECT_CALL(stream, GetPacket(42));

    reader.ReadPacket(&stream, 42);
}

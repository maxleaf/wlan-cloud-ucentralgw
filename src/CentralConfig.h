//
//	License type: BSD 3-Clause License
//	License copy: https://github.com/Telecominfraproject/wlan-cloud-ucentralgw/blob/master/LICENSE
//
//	Created by Stephane Bourque on 2021-03-04.
//	Arilia Wireless Inc.
//

#ifndef UCENTRAL_UCENTRALCONFIG_H
#define UCENTRAL_UCENTRALCONFIG_H

#include <string>
#include "Poco/JSON/Object.h"

namespace uCentral::Config {

	class Config {
    public:
        explicit Config(const std::string &Config)
        :Config_(Config) {}

        Config();

		static void Init();
        bool SetUUID(uint64_t UUID);
        [[nodiscard]] bool Valid();
		[[nodiscard]] std::string get() { return Config_; };
		[[nodiscard]] static std::string Default();
		[[nodiscard]] static std::string Default_Old();
		[[nodiscard]] Poco::JSON::Object::Ptr to_json();

    private:
        std::string Config_;
    };

    class Capabilities {
    public:
        explicit Capabilities(std::string Caps)
        :   Capabilities_(std::move(Caps))
        {

        }

        Capabilities()
        {
            Capabilities_ = Default();
        }

        static std::string Default();
        [[nodiscard]] const std::string & Get() const { return Capabilities_; };
        [[nodiscard]] const std::string & Compatible();
        [[nodiscard]] const std::string & Model();
		[[nodiscard]] const std::string & Platform();

    private:
        std::string Capabilities_;
        bool        Parsed_=false;
        std::string Compatible_;
        std::string Model_;
		std::string Platform_;

		void Parse();
    };

} // namespace

#endif //UCENTRAL_UCENTRALCONFIG_H

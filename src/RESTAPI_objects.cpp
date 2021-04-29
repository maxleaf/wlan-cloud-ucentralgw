//
// Created by stephane bourque on 2021-03-04.
//

#include "RESTAPI_objects.h"
#include "RESTAPI_handler.h"

#include "Poco/JSON/Parser.h"
#include "Poco/JSON/Stringifier.h"

Poco::JSON::Object uCentralDevice::to_json() const
{
    Poco::JSON::Object  Obj;

    Obj.set("serialNumber",SerialNumber);
    Obj.set("deviceType",DeviceType);
    Obj.set("macAddress",MACAddress);
    Obj.set("manufacturer",Manufacturer);
    Obj.set("UUID",UUID);

	Poco::JSON::Parser	P;
	Poco::Dynamic::Var result = P.parse(Configuration);
	const auto & CfgObj = result.extract<Poco::JSON::Object::Ptr>();
	Obj.set("configuration",CfgObj);

    Obj.set("notes",Notes);
    Obj.set("createdTimestamp",RESTAPIHandler::to_RFC3339(CreationTimestamp));
    Obj.set("lastConfigurationChange",RESTAPIHandler::to_RFC3339(LastConfigurationChange));
    Obj.set("lastConfigurationDownload",RESTAPIHandler::to_RFC3339(LastConfigurationDownload));
	Obj.set("owner",Owner);
	Obj.set("location",Location);

    return Obj;
}

bool uCentralDevice::from_json(Poco::JSON::Object::Ptr Obj) {

    try {
        Poco::DynamicStruct ds = *Obj;

        SerialNumber = ds["serialNumber"].toString();
        DeviceType = ds["deviceType"].toString();
        MACAddress = ds["macAddress"].toString();
        UUID = ds["UUID"];
        // Configuration = ds["configuration"].toString();

        if(ds.contains("notes"))
            Notes = ds["notes"].toString();
        if(ds.contains("manufacturer"))
            Manufacturer = ds["manufacturer"].toString();
		if(ds.contains("owner"))
			Owner = ds["owner"].toString();
		if(ds.contains("location"))
			Location = ds["location"].toString();

        return true;
    }
    catch (const Poco::Exception &E )
    {

    }

    return false;
}

void uCentralDevice::Print() const {
    std::cout << "Device: " << SerialNumber << " "
                            << DeviceType << " "
                            << MACAddress << " "
                            << Manufacturer << " "
                            << Configuration << std::endl;
}

Poco::JSON::Object uCentralStatistics::to_json() const {
    Poco::JSON::Object  Obj;
    Obj.set("UUID",UUID);

	Poco::JSON::Parser	P;
	Poco::Dynamic::Var result = P.parse(Data);
	const auto & CfgObj = result.extract<Poco::JSON::Object::Ptr>();
	Obj.set("data",CfgObj);

	Obj.set("recorded",RESTAPIHandler::to_RFC3339(Recorded));
    return Obj;
}

Poco::JSON::Object uCentralCapabilities::to_json() const {

    Poco::JSON::Object  Obj;

	Poco::JSON::Parser	P;
	Poco::Dynamic::Var result = P.parse(Capabilities);
	const auto & CfgObj = result.extract<Poco::JSON::Object::Ptr>();
	Obj.set("capabilities",CfgObj);

    Obj.set("firstUpdate",RESTAPIHandler::to_RFC3339(FirstUpdate));
    Obj.set("lastUpdate",RESTAPIHandler::to_RFC3339(LastUpdate));
    return Obj;
}

Poco::JSON::Object uCentralDeviceLog::to_json() const
{
    Poco::JSON::Object  Obj;
    Obj.set("log",Log);
    Obj.set("severity",Severity);

	Poco::JSON::Parser	P;
	Poco::Dynamic::Var result = P.parse(Data);
	const auto & CfgObj = result.extract<Poco::JSON::Object::Ptr>();
	Obj.set("data",CfgObj);

    Obj.set("recorded",RESTAPIHandler::to_RFC3339(Recorded));
    Obj.set("logType",LogType);
    return Obj;
}

Poco::JSON::Object  uCentralHealthCheck::to_json() const {
    Poco::JSON::Object  Obj;
    Obj.set("UUID",UUID);

	Poco::JSON::Parser	P;
	Poco::Dynamic::Var result = P.parse(Data);
	const auto & CfgObj = result.extract<Poco::JSON::Object::Ptr>();
	Obj.set("values",CfgObj);

    Obj.set("sanity",Sanity);
    Obj.set("recorded",RESTAPIHandler::to_RFC3339(Recorded));
    return Obj;
}

/*
    std::string     Configuration;
    std::string     Models;
    uint64_t        Created;
    uint64_t        LastModified;
    [[nodiscard]] Poco::JSON::Object to_json() const;
    bool from_JSON(Poco::JSON::Object::Ptr Obj);
 */
Poco::JSON::Object uCentralDefaultConfiguration::to_json() const {
    Poco::JSON::Object  Obj;
    Obj.set("name",Name);
    Obj.set("modelIds",Models);
    Obj.set("description",Description);

	Poco::JSON::Parser	P;
	Poco::Dynamic::Var result = P.parse(Configuration);
	const auto & CfgObj = result.extract<Poco::JSON::Object::Ptr>();
	Obj.set("configuration",CfgObj);

    Obj.set("created",RESTAPIHandler::to_RFC3339(Created));
    Obj.set("lastModified",RESTAPIHandler::to_RFC3339(LastModified));
    return Obj;
}

Poco::JSON::Object uCentralCommandDetails::to_json() const {
    Poco::JSON::Object  Obj;
    Obj.set("UUID",UUID);
    Obj.set("serialNumber",SerialNumber);
    Obj.set("command",Command);

	Poco::JSON::Parser	P;
	Poco::Dynamic::Var result = P.parse(Details);
	const auto & CfgObj = result.extract<Poco::JSON::Object::Ptr>();
	Obj.set("details",CfgObj);

	Poco::JSON::Parser	P2;
	Poco::Dynamic::Var result2 = P.parse(Results);
	const auto & ResultsObj2 = result.extract<Poco::JSON::Object::Ptr>();
	Obj.set("results",ResultsObj2);

    Obj.set("errorText", ErrorText);
    Obj.set("submittedBy",SubmittedBy);
    Obj.set("status",Status);
    Obj.set("submitted",RESTAPIHandler::to_RFC3339(Submitted));
    Obj.set("executed",RESTAPIHandler::to_RFC3339(Executed));
    Obj.set("completed",RESTAPIHandler::to_RFC3339(Completed));
    Obj.set("when",RESTAPIHandler::to_RFC3339(RunAt));
    Obj.set("errorCode",ErrorCode);
    Obj.set("custom",Custom);
    Obj.set("waitingForFile", WaitingForFile);
    Obj.set("attachFile",RESTAPIHandler::to_RFC3339(AttachDate));
    return Obj;
}

bool uCentralDefaultConfiguration::from_json(Poco::JSON::Object::Ptr Obj) {
    Poco::DynamicStruct ds = *Obj;

    try {
        Name = ds["name"].toString();
        Configuration = ds["configuration"].toString();
        Models = ds["modelIds"].toString();
        if (ds.contains("description"))
            Description = ds["description"].toString();
        return true;
    }
    catch (const Poco::Exception & E )
    {

    }

    return false;
}

Poco::JSON::Object uCentralBlackListedDevice::to_json() const {
	Poco::JSON::Object  Obj;
	Obj.set("serialNumber",SerialNumber);
	Obj.set("author",Author);
	Obj.set("reason",Reason);
	Obj.set("created",RESTAPIHandler::to_RFC3339(Created));
	return Obj;
}

#include "ReadyRspRsp.hpp"

#include <rapidjson/document.h>
#include <rapidxml/rapidxml.hpp>

#include "JSONLib/Deserialize.hpp"
#include "JSONLib/Serialize.hpp"
#include "XMLLib/Deserialize.hpp"
#include "XMLLib/Serialize.hpp"

#pragma warning(push)
#pragma warning(disable : 4267)
#include "ProtoLib/ReadyRspRsp.pb.h"
#pragma warning(pop)

namespace
{
  const std::string N_GAME_ID("gameId");
}

msg::ReadyRspRsp::ReadyRspRsp()
{
}

msg::ReadyRspRsp::ReadyRspRsp(int gameId)
  : m_gameId(gameId)
{
}

bool msg::ReadyRspRsp::parseFromJson(const std::string& msg)
{
  rapidjson::Document json(rapidjson::kObjectType);
  json.Parse(msg.c_str());
  m_gameId = json::getInt(json, N_GAME_ID);
  return true;
}

bool msg::ReadyRspRsp::parseFromProto(const std::string& msg)
{
  proto::ReadyRspRsp m;
  m.ParseFromString(msg);
  m_gameId = m.gameid();
  return true;
}

bool msg::ReadyRspRsp::parseFromXml(const std::string& msg)
{
  auto pDoc = new rapidxml::xml_document<>;
  char* cstr = new char[msg.size() + 1];
  strcpy(cstr, msg.c_str());
  pDoc->parse<0>(cstr);
  m_gameId = static_cast<int>(xml::getNumber(pDoc, N_GAME_ID));
  delete[] cstr;
  delete pDoc;
  return true;
}

std::string msg::ReadyRspRsp::toJsonString() const
{
  rapidjson::Document doc(rapidjson::kObjectType);
  json::addIntToDoc(doc, N_GAME_ID, m_gameId);
  return json::jsonToString(doc);
}

std::string msg::ReadyRspRsp::toProtoString() const
{
  proto::ReadyRspRsp msg;
  msg.set_gameid(m_gameId);
  return msg.SerializeAsString();
}

std::string msg::ReadyRspRsp::toXMLString() const
{
  auto pDoc = new rapidxml::xml_document<>;
  xml::addDataToNode(pDoc, N_GAME_ID, static_cast<int>(m_gameId));
  auto toReturn = xml::xmlToString(pDoc);
  delete pDoc;
  return toReturn;
}

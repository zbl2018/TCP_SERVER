#include"./include/MyJson.h"
int MyJson::decodejson(string json_data){
    Json::Reader reader;
    Json::Value value;
    PlanPath_node one_node;
    try{
         //cout<<"222"<<endl;
         if(reader.parse(json_data,value)){
            if(value["action"].isNull()){
                    return ACT_NULL;
                }
                else {
                    //依据action进行json解析
                    action = value["action"].asString();

                    if(action.compare("patrolStartPathPlan")==0){
                        //cout<<"equal"<<endl;
                        for(int i = 0;i<value["mapNodeList"].size();i++){
                            result = value["result"].asString();
                            if(result.compare(FAIL)==0){
                                    return RES_FAIL;
                                }
                            serial = value["serial"].asString();
                            msg = value["msg"].asString();
                            one_node.x = value["mapNodeList"][i]["x"].asDouble();
                            one_node.y = value["mapNodeList"][i]["y"].asDouble();
                            one_node.no = value["mapNodeList"][i]["no"].asInt();
                            one_node.id = value["mapNodeList"][i]["id"].asString();
                            PlanPath_info.push_back(one_node);
                        }
                        action_type = PLANPATH_RES;
                        //cout<<"json suc!"<<endl;
                        return RES_SUCC;                           
                    }

                    if(action.compare("RosState")==0){
                        action_type = RosState_RES;
                        //cout<<"json suc!"<<endl;
                        return RES_SUCC;      
                    // value["action"] = "RosRealState";
                    // value["content"]["direction"]["carDirection"] = heading;
                    // value["content"]["direction"]["flTire"] = cangle1;
                    // value["content"]["direction"]["frTire"] = cangle2;
                    // value["content"]["direction"]["rlTire"] = cangle3;
                    // value["content"]["direction"]["rrTire"] = cangle4;
                    // value["content"]["model"] = cmode;
                    // value["content"]["speed"]["carSpeed"] = cspeed;
                    // value["content"]["speed"]["flSpeed"] = cspeed_m1;
                    // value["content"]["speed"]["frSpeed"] = cspeed_m2;
                    // value["content"]["speed"]["rlSpeed"] = cspeed_m3;
                    // value["content"]["speed"]["rrSpeed"] = cspeed_m4;
                    // value["content"]["x"] = lat_now;
                    // value["content"]["y"] = lon_now;
                    // value["serial"] = "12345678";
                     }
                     if(action.compare("RosRealState")==0){
                         action_type = RosRealState_RES;
                        //cout<<"json suc!"<<endl;
                        return RES_SUCC;      
                     }
                     
                    
                }
            }
    }
    catch(exception &e){
        cout<<e.what()<<endl;
        return CATCH_ERROR;
    }
    return RES_SUCC;
    } 
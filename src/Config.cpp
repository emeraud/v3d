#include "Config.hpp"

#include <iostream>

Config::Config() {
  pugi::xml_document doc;
  pugi::xml_parse_result result = doc.load_file("config.xml");
  if (result) {
    // screen
    pugi::xpath_node display = doc.select_node("//display");
    pugi::xml_node screen = display.node().child("screen");
    width = screen.attribute("width").as_int();
    height = screen.attribute("height").as_int();

    std::cout << "width=" << width << std::endl;
    std::cout << "height=" << height << std::endl;

    // render
    pugi::xpath_node renderN = doc.select_node("//render");
    pugi::xml_node render = renderN.node();
    withShadow = render.attribute("withShadow").as_bool();
    withLightSource = render.attribute("withLightSource").as_bool();

    std::cout << "withShadow=" << withShadow << std::endl;
    std::cout << "withLightSource=" << withLightSource << std::endl;

    // tuning
    pugi::xpath_node tuning = doc.select_node("//tuning");
    pugi::xml_node threading = tuning.node().child("threading");
    nbThreads = threading.attribute("nbThreads").as_int();

    std::cout << "nbThreads=" << nbThreads << std::endl;

  } else {
    std::cout << "Could not load config" << std::endl;
    std::cout << "Error description: " << result.description() << std::endl;
    std::cout << "Error offset: " << result.offset << " (error at [..." << (result.offset) << "]" << std::endl;    
    exit(0);
  }

}

Config::~Config() {

}

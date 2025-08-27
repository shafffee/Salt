#pragma once
#include <vector>
#include "Vertex.h"
#include <map>
#include <string>
#include <sstream>

namespace salt::Utils{

inline void load_obj(std::vector<Vertex>* verticies, std::vector<uint32_t>* indices, std::string obj, glm::mat4 transform_matrix = glm::mat4(1.0f)) {
  
  std::vector<glm::vec3> positions;
  std::vector<glm::vec3> normals;
  std::vector<glm::vec2> texcoords;

  //  pos/norm/uv  index of vertex
  //map that has a vertex index for every v/vn/vt
  std::map<std::tuple<uint32_t, uint32_t, uint32_t>, uint32_t> vmap;


  std::istringstream stream(obj);
  std::string line;
  while (std::getline(stream, line)){

    // Пропуск пустых строк и комментариев
    if (line.empty() || line[0] == '#') continue;

    std::istringstream line_stream(line);
    std::string type;
    line_stream >> type;

    if (type == "v") {  // Позиции вершин
      glm::vec3 pos;
      line_stream >> pos.x >> pos.y >> pos.z;
      positions.push_back(pos);
    }
    else if (type == "vt") {  // Текстурные координаты
      glm::vec2 uv;
      line_stream >> uv.x >> uv.y;
      uv.y = 1.0f - uv.y;  // Инвертируем для OpenGL
      texcoords.push_back(uv);
    }
    else if (type == "vn") {  // Нормали
      glm::vec3 n;
      line_stream >> n.x >> n.y >> n.z;
      normals.push_back(n);
    }
    else if (type == "f") {  // Грани
      std::string vertex_str;
      uint32_t first_index = 0;   // Первая вершина полигона
      uint32_t prev_index = 0;    // Предыдущая обработанная вершина
      int vertex_count = 0;       // Счетчик вершин в полигоне

      while (line_stream >> vertex_str) {
        // Парсим комбинацию индексов
        int v_idx = 0, vt_idx = 0, vn_idx = 0;
        char temp;
        std::istringstream v_stream(vertex_str);

        // Простая обработка форматов: v, v/vt, v//vn, v/vt/vn
        v_stream >> v_idx;
        if (v_stream.peek() == '/') {
          v_stream >> temp;
          if (v_stream.peek() != '/') v_stream >> vt_idx;
          if (v_stream.peek() == '/') {
            v_stream >> temp >> vn_idx;
          }
        }

        // Преобразование индексов
        uint32_t p_idx = (v_idx > 0) ? v_idx - 1 : positions.size() + v_idx;
        uint32_t t_idx = (vt_idx > 0) ? vt_idx - 1 : (vt_idx < 0) ? texcoords.size() + vt_idx : -1;
        uint32_t n_idx = (vn_idx > 0) ? vn_idx - 1 : (vn_idx < 0) ? normals.size() + vn_idx : -1;

        if (p_idx >= positions.size()) {
          salt::Logging::Error("Error while loading an obj model: v index out of range");
          continue;
        };
        if (t_idx >= texcoords.size()) {
          salt::Logging::Error("Error while loading an obj model: vt index out of range");
          continue;
        };
        if (n_idx >= normals.size()) {
          salt::Logging::Error("Error while loading an obj model: vn index out of range");
          continue;
        };

        // Обработка вершины и получение индекса
        uint32_t current_index;
        if (vmap.count(std::tuple<uint32_t, uint32_t, uint32_t>( p_idx ,t_idx, n_idx ))) current_index = vmap[{ p_idx, t_idx, n_idx }]; //if already have a vertex, get its index
        else {
          current_index = verticies->size();
          Vertex vert;
          glm::vec4 transformed = transform_matrix * glm::vec4(positions[p_idx], 1.0f);
          vert.Position = glm::vec3(transformed / transformed.w);
          vert.Normal = normals[n_idx];
          vert.TexCoords = texcoords[t_idx];
          verticies->push_back(vert);
        }

        if (vertex_count == 0) {
          // Первая вершина полигона
          first_index = current_index;
        }
        else if (vertex_count == 1) {
          // Вторая вершина - запоминаем для треугольников
          prev_index = current_index;
        }
        else {
          // Формируем треугольник: [первая, предыдущая, текущая]
          indices->push_back(first_index);
          indices->push_back(prev_index);
          indices->push_back(current_index);
          // Текущая вершина становится предыдущей для следующего треугольника
          prev_index = current_index;
        }

        vertex_count++;
      }
    }

  }

  salt::Logging::Debug(std::to_string(verticies->size()));

}

}
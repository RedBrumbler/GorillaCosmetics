#include "Types/Material/Material.hpp"
#include "cosmeticsloader/shared/CosmeticLoader.hpp"
#include "logging.hpp"

using namespace CosmeticsLoader;

namespace GorillaCosmetics
{
    Material::Material(std::string path) : manifest(MaterialManifest(path)) {};

    void Material::Load()
    {
        CosmeticLoader<MaterialManifest>* loader = new CosmeticLoader<MaterialManifest>(manifest, [&, loader](std::string name , Il2CppObject* obj){
            INFO("Loaded Material %s", this->manifest.get_descriptor().get_name().c_str());            
            this->object = obj;
            //delete(loader);
        }, "_Material", il2cpp_utils::GetSystemType("UnityEngine", "GameObject"));
    }

    const Config& Material::get_config() const
    {
        return manifest.get_config();
    }

    const Descriptor& Material::get_descriptor() const
    {
        return manifest.get_descriptor();
    }

    const Material::MaterialManifest& Material::get_manifest() const
    {
        return manifest;
    }
    
    Il2CppObject* Material::get_material()
    {
        if (!object) ERROR("Asked for Material object but it was nullptr!");
        return object;
    }
}
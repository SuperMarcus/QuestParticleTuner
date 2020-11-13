#include "Config.hpp"
#include "particletune_private.hpp"

#define SET_PRIMITIVE(doc, name, type, value, alloc) \
    if (doc .HasMember(name)) { \
        doc [name].Set ## type (value); \
    } else { \
        doc .AddMember(name, value, alloc); \
    }

#define GET_PRIMITIVE(doc, name, type, default) \
    doc .HasMember(name) && doc[name].Is ## type () \
    ? doc [name].Get ## type () : (default)

ConfigClass::ConfigClass(Configuration& storage): _storage(storage) {
    load();
}

void ConfigClass::load() {
    getLogger().info("Loading configurations...");

    _storage.Load();
    auto& document = _storage.config;
    
    sparkleMultiplier = GET_PRIMITIVE(document, "sparkles_multiplier", Float, PT_DEFAULT_SPARKLE_MULTIPLIER);
    explosionMultiplier = GET_PRIMITIVE(document, "explosion_multiplier", Float, PT_DEFAULT_EXPLOSION_MULTIPLIER);
    lifetimeMultiplier = GET_PRIMITIVE(document, "lifetime_multiplier", Float, PT_DEFAULT_LIFETIME_MULTIPLIER);
    rainbowParticles = GET_PRIMITIVE(document, "rainbow_particles", Bool, false);
    reduceCoreParticles = GET_PRIMITIVE(document, "reduce_core_particles", Bool, false);
    reduceClashParticles = GET_PRIMITIVE(document, "reduce_clash_particles", Bool, false);
    reduceDustParticles = GET_PRIMITIVE(document, "reduce_dust_particles", Bool, false);
}

void ConfigClass::store() {
    auto& document = _storage.config;
    auto& allocator = document.GetAllocator();

    SET_PRIMITIVE(document, "sparkles_multiplier", Float, sparkleMultiplier, allocator);
    SET_PRIMITIVE(document, "explosion_multiplier", Float, explosionMultiplier, allocator);
    SET_PRIMITIVE(document, "lifetime_multiplier", Float, lifetimeMultiplier, allocator);
    SET_PRIMITIVE(document, "rainbow_particles", Bool, rainbowParticles, allocator);
    SET_PRIMITIVE(document, "reduce_core_particles", Bool, reduceCoreParticles, allocator);
    SET_PRIMITIVE(document, "reduce_clash_particles", Bool, reduceClashParticles, allocator);
    SET_PRIMITIVE(document, "reduce_dust_particles", Bool, reduceDustParticles, allocator);

    _storage.Write();
    getLogger().info("Configuration updated.");
}

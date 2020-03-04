#pragma once
#include "ModHandler.h"
#include <filesystem>
#include "Json.h"
#include "zip/ttvfs/ttvfs.h"
#include "hooking.h"
#include "util/TopologicalSort.h"

using namespace SML;
using namespace Mod;

typedef std::string FileHash;

void iterateDependencies(std::unordered_map<std::wstring, FModLoadingEntry>& loadingEntries,
	std::unordered_map<std::wstring, uint64_t>& modIndices,
	const FModInfo& selfInfo,
	std::vector<std::wstring>& missingDependencies,
	TopologicalSort::DirectedGraph<uint64_t>& sortGraph,
	const std::unordered_map<std::wstring, FVersionRange>& dependencies,
	bool optional);

void finalizeSortingResults(std::unordered_map<uint64_t, std::wstring>& modByIndex,
	std::unordered_map<std::wstring, FModLoadingEntry>& loadingEntries,
	std::vector<uint64_t>& sortedIndices);

void populateSortedModList(std::unordered_map<uint64_t, std::wstring>& modByIndex,
	std::unordered_map<std::wstring, FModLoadingEntry>& loadingEntries,
	std::vector<uint64_t>& sortedIndices,
	std::vector<FModLoadingEntry>& sortedModLoadingList);

IModuleInterface* InitializeSMLModule();

FModPakLoadEntry CreatePakLoadEntry(const std::wstring& modid);

FModLoadingEntry createSMLLoadingEntry();

std::wstring getModIdFromFile(const path& filePath);

bool extractArchiveFile(const path& outFilePath, ttvfs::File* obj);

TSharedPtr<FJsonObject> readArchiveJson(ttvfs::File* obj);

FileHash hashArchiveFileContents(ttvfs::File* obj);

bool extractArchiveObject(ttvfs::Dir& root, const std::string& objectType, const std::string& archivePath, SML::Mod::FModLoadingEntry& loadingEntry, const FJsonObject* metadata);

bool extractArchiveObjects(ttvfs::Dir& root, const FJsonObject& dataJson, SML::Mod::FModLoadingEntry& loadingEntry);

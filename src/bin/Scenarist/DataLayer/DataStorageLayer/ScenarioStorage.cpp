#include "ScenarioStorage.h"

#include <DataLayer/DataMappingLayer/MapperFacade.h>
#include <DataLayer/DataMappingLayer/ScenarioMapper.h>

#include <Domain/Scenario.h>

#include <QUuid>

using namespace DataStorageLayer;
using namespace DataMappingLayer;


ScenariosTable* ScenarioStorage::all()
{
	if (m_all == 0) {
		m_all = MapperFacade::scenarioMapper()->findAll();
	}
	return m_all;
}

Scenario* ScenarioStorage::current(bool _isDraft)
{
	Scenario* currentScenario = 0;
	if (all()->count() > 0) {
		foreach (DomainObject* domainObject, all()->toList()) {
			if (Scenario* scenario = dynamic_cast<Scenario*>(domainObject)) {
				if (scenario->isDraft() == _isDraft) {
					currentScenario = scenario;
					break;
				}
			}
		}
	}

	//
	// Если сценарий ещё не был создан
	//
	if (currentScenario == 0) {
		//
		// ... создаём сценарий
		//
		currentScenario = new Scenario(Identifier(), QString::null, QString::null, QString::null);
		currentScenario->setIsDraft(_isDraft);
		//
		// ... сохраним сценарий в базе данных
		//
		MapperFacade::scenarioMapper()->insert(currentScenario);
		//
		// ... добавим в список
		//
		all()->append(currentScenario);
	}

	return currentScenario;
}

void ScenarioStorage::storeScenario(Scenario* _scenario)
{
	Q_ASSERT(_scenario);

	MapperFacade::scenarioMapper()->update(_scenario);
}

void ScenarioStorage::clear()
{
	delete m_all;
	m_all = 0;

	MapperFacade::scenarioMapper()->clear();
}

ScenarioStorage::ScenarioStorage() :
	m_all(0)
{
}

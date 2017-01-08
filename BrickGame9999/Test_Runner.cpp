#include "Test_Runner.hpp"
#include "Global.hpp"

#include "Test.hpp"
#include "Test_Ticker.hpp"

namespace Test
{
	void Runner::run()
	{
		l.log(Logger::INFO, "====== Starting test suite ");

		AbstractTest *ticker = new Test_Ticker();
		ticker->runTest(*this);
		delete ticker;

		this->end();
	}

	Runner::Runner()
	{
		this->successfulTestsTotal = 0;
		this->testsTotal = 0;
		
		this->resetSet();
	}

	void Runner::newSet(std::string name)
	{
		this->setStarted = true;
		this->setName = name;

		l.log(Logger::INFO, "=== Starting test set [%s]", this->setName.c_str());
	};

	void Runner::endSet()
	{
		if (!this->setStarted)
		{
			throw string("ending set without having started it");
		}

		this->testsTotal += this->testsInSet;
		this->successfulTestsTotal += this->successfulTestsInSet;

		l.logPartial(static_cast<Logger::Tag>(Logger::INFO), "=== Completed test set [%s]: ", this->setName.c_str());
		
		this->logRunStatus(this->successfulTestsInSet, this->testsInSet);

		l.setDefaultColor();

		l.logContinue("[%d/%d]", this->successfulTestsInSet, this->testsInSet);

		this->resetSet();
	};

	void Runner::resetSet()
	{
		this->setName = "";
		this->testsInSet = 0;
		this->successfulTestsInSet = 0;
		this->setStarted = false;
	}

	void Runner::end()
	{
		l.logPartial(static_cast<Logger::Tag>(Logger::INFO), "====== Completed test suite: ");

		this->logRunStatus(this->successfulTestsTotal, this->testsTotal);

		l.logContinue("[%d/%d]", this->successfulTestsTotal, this->testsTotal);
	}

	void Runner::logRunStatus(int successful, int total)
	{
		if (!l.inPartial())
		{
			throw string("logging run status while not in partial log mode");
		}

		if (successful == total)
		{
			l.setColor({ static_cast<Logger::ForegroundColor>(Logger::FG_GREEN), static_cast<Logger::BackgroundColor>(Logger::BG_BLACK) });
			l.logContinue("successfull ");
		}
		else if (successful == 0 && total != 0)
		{
			l.setColor({ static_cast<Logger::ForegroundColor>(Logger::FG_RED), static_cast<Logger::BackgroundColor>(Logger::BG_BLACK) });
			l.logContinue("failed ");
		}
		else
		{
			l.setColor({ static_cast<Logger::ForegroundColor>(Logger::FG_YELLOW), static_cast<Logger::BackgroundColor>(Logger::BG_BLACK) });
			l.logContinue("partial ");
		}

		l.setDefaultColor();
	}

	void Runner::logTestStatus(bool success)
	{
		if (!l.inPartial())
		{
			throw string("logging run status while not in partial log mode");
		}

		if (success)
		{
			l.setColor({ static_cast<Logger::ForegroundColor>(Logger::FG_GREEN), static_cast<Logger::BackgroundColor>(Logger::BG_BLACK) });
			l.logContinue("OK!");
		}
		else
		{
			l.setColor({ static_cast<Logger::ForegroundColor>(Logger::FG_RED), static_cast<Logger::BackgroundColor>(Logger::BG_BLACK) });
			l.logContinue("failed");
		}

		l.setDefaultColor();
	}

	void Runner::test(bool condition, std::string description)
	{
		if (!this->setStarted)
		{
			throw string("running test while not in set");
		}

		l.logPartial(Logger::DEBUG, "%s: ", description.c_str());
		this->logTestStatus(condition);

		if (condition)
		{
			this->successfulTestsInSet += 1;
		}
		this->testsInSet += 1;
	}

	void Runner::test(int actual, int expected, std::string description)
	{
		this->test(actual == expected, description);
		l.logContinue(" -- expected %d, got %d", expected, actual);
	}
}
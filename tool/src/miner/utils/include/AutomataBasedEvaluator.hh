#include "Automaton.hh"
#include "Evaluator.hh"
#include "Location.hh"
#include "Semaphore.hh"
#include "Trace.hh"
#include "Trinary.hh"
#include "formula/temporal/TemporalExpression.hh"
#include "spot/twa/twagraph.hh"

namespace harm {
class PlaceholderPack;

///@brief This class is used to evaluate a formula using an automaton
class AutomataBasedEvaluator : public Evaluator {

public:
  AutomataBasedEvaluator(const TemporalExpressionPtr &formula,
                         const harm::TracePtr &trace);
  ~AutomataBasedEvaluator();

  /// \brief evaluate the formula at a given time through a linear algorithm
  std::pair<Trinary, size_t> evaluate(size_t time) override;

  /// \brief directly evaluate the automaton through a quadratic algorithm
  template <bool Dynamic>
  std::pair<Trinary, size_t> evaluateAutomaton(size_t time);

  Automaton *getAutomaton() { return _automaton; }

private:
  /** \brief evaluation: 1. this function handles the update of cached values and the dynamic or non-dynamic shift case 
   * \param what specifies if the function has to update the cached values of ant/con/both/none
   */
  void linearEval(harm::Location what);

  /** \brief evaluation: 2. this function handles the cuts in the trace (the traces may contain 'cuts' if it was generated by merging several input traces, the simples case only have one cut, that is, only one input trace)
   */
  template <bool Dynamic> void evalWithCut();

  /** \brief evaluation: 3. this function handles l1 multithreading
   * \param cachedValues of the ant or con
   */
  template <bool Dynamic>
  void linearEval(Range traceRange, Range threadsRange,
                  ProtectedQueueNotify<Range> &threadsPool);

  /** \brief evaluation: 4. actually runs the evaluation algorithm using thread nThread
   * \param traceRange corresponds the sub-trace to be evaluated
   * \param threadsRange contains information on the threads currently in use
   */
  template <bool Dynamic>
  void runLinearEval(Range &traceRange, const Range &threadsRange,
                     size_t nThread = 0);

  /** \brief evaluation: 5. join data concurrently generated by multithreading
   */
  template <bool Dynamic>
  void joinData(Range traceRange, const Range &threadsRange);

  void generateAutomaton();

  void initCache();

  void changeTrace(const harm::TracePtr &trace) override;

  ///shift between the current time and the time of the sere match
  size_t *_sereShiftCache = nullptr;
  ///additional cache to enable parallelism when evaluating a sere
  size_t **_sereShiftCacheParallel = nullptr;

  ///these are the cached truth values of the formula
  Trinary *_cache = nullptr;
  ///additional cached values to enable parallelism
  Trinary **_cacheParallel = nullptr;
  ///the automaton that represents the formula
  Automaton *_automaton = nullptr;
};
// shared pointer to the AutomataBasedEvaluator
using AutomataBasedEvaluatorPtr =
    std::shared_ptr<AutomataBasedEvaluator>;

std::shared_ptr<spot::twa_graph>
generateDeterministicSpotAutomaton(const spot::formula &formula);

/** \brief builds a custom automaton (see class Automaton) from a spotLTL automaton
   */
Automaton *buildAutomatonFromSpot(spot::twa_graph_ptr &automata,
                                  const PlaceholderPack &pack);
Automaton *
generateAutomatonFromTemporal(const TemporalExpressionPtr &formula);
} // namespace harm

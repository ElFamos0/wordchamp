<template>
  <div>
    <div v-for="entry in entries" :key="entry.id">
        <div>
          <HistoryEntry @show-details="showDetails"
          :entryId="entry.id" :solution="entry.solution" :result="entry.result" :date="entry.date" :type="entry.type"
          />
        </div>
        <div>
          <DetailedEntry v-if="toggled[entry.id]" :entryId="entry.id" :solution="entry.solution" :result="entry.result" :guesses="entry.guesses" :maxtry="entry.maxtry"/>
        </div>
    </div>
  </div>
</template>


<script>
import HistoryEntry from './HistoryEntry.vue'
import DetailedEntry from '../components/DetailedEntry.vue'

export default {
  name: 'HistoryTable',
  props: {
      entries: Array
  },
  components: {
    HistoryEntry,
    DetailedEntry,
  },
  emits: ['show-details'],
  methods: {
      showDetails(entryId) {
        // console.log("vous avez cliqué sur l'entrée ", entryId, " toggle valait ", this.toggled[entryId])
        this.toggled[entryId]=!this.toggled[entryId]
      }
  },
  data() {
    return {
        toggled: {},
    }
  },
  created() {
    for (let i = 0; i < this.entries.length; i++) {
      this.toggled[this.entries[i].id] = false
    }
  }
}

</script>

<style scoped>

</style>
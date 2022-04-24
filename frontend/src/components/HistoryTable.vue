<template>
  <div>
    <div v-for="entry in entries" :key="entry.id">
        <div>
          <HistoryEntry @show-details="showDetails"
          :entryId="entry.id" :solution="entry.solution" :result="entry.result"
          />
        </div>
        <div>
          <DetailedEntry v-if="detailsToggled[entry.id]" :entryId="entry.id" :solution="entry.solution" :result="entry.result" :guesses="entry.guesses"/>
          <br>
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
        console.log("vous avez cliqué sur l'entrée ", entryId)
        this.detailsToggled[entryId]=!this.detailsToggled[entryId]
      }
  },
  data() {
    return {
      detailsToggled:[false, true, false, true, false, true]
    }
  }
}

</script>

<style scoped>

</style>
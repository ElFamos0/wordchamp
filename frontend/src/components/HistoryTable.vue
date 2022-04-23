<template>
  <div>
    <div v-for="entry in entries" :key="entry.id">
        <HistoryEntry @show-details="$emit('show-details', entry.id)" 
        :entryId="entry.id" :motFinal="entry.motFinal" :result="entry.result"
        />
    </div>
  </div>
</template>


<script>
import HistoryEntry from './HistoryEntry.vue'

export default {
  name: 'HistoryTable',
  props: {
      entries: Array
  },
  components: {
    HistoryEntry,
  },
  emits: ['show-details'],
}
</script>

<style scoped>

</style>
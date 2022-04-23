<template>
  <div>
    <div v-for="entry in entries" :key="entry.id">
        <HistoryEntry :entryId="entry.id" :motFinal="entry.motFinal" :result="entry.result"/>
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
  emits: [],
}
</script>

<style scoped>

</style>
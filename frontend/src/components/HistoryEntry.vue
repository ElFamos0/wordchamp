<template>
    <div class="container">
        <div>Id : {{entryId}}</div>
        <div>Mot final : {{motFinal}}</div>
        <div>{{result}}</div>
    </div>
</template>


<script>
export default {
  name: 'HistoryEntry',
  props: {
    entryId : String,
    motFinal : String,
    result: String,
  },
  components: {
  },
  emits: [],
}
</script>


<style scoped>
.container {
  margin: 10px auto;
  overflow: auto;
  border: 2px solid rgb(55, 16, 229);
  padding: 10px;
  border-radius: 5px;
}
</style>